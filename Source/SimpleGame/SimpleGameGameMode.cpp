// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleGameGameMode.h"
#include "UObject/ConstructorHelpers.h"

#include "GameState/BattleFieldState.h"
#include "GameState/InventoryState.h"

ASimpleGameGameMode::ASimpleGameGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/UMG/Common/W_Master"));
	if (WidgetClassFinder.Class != NULL) {
		rootUI = WidgetClassFinder.Class;
	}
}

void ASimpleGameGameMode::StartPlay() 
{
	Super::StartPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), rootUI);
	if (Widget) {
		Widget->AddToViewport();
	}

	GameFSM = NewObject<UFSM>(this, TEXT("SimpleGameFSM"));
	if (!IsValid(GameFSM)) {
		Logout(nullptr);
		return;
	}

	FSM_ADDSTATE(GameFSM, UInventoryState);
	FSM_ADDSTATE(GameFSM, UBattleFieldState);

	ChangeStateEnum(EGameState::INVENTORY);
}

void ASimpleGameGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (!IsValid(GameFSM))
	{
		GameFSM->Release();
	}
}

void ASimpleGameGameMode::ChangeStateEnum(EGameState state)
{
	if (state != EGameState::NONE
		&& state != LobbyCurState)
	{
		LobbyPrevState = LobbyCurState;
		LobbyCurState = state;
	}

	switch (LobbyCurState)
	{
	case EGameState::INVENTORY:
		ChangeState(UInventoryState::StaticClass());
		break;
	case EGameState::BATTLEFIELD:
		ChangeState(UBattleFieldState::StaticClass());
		break;

	case EGameState::NONE:
	default:
		/*UE_LOG(LogTemp, Log, TEXT("%s does not support prev / next state, requested : [%s]"), *GET_ENUM_STRING("EGameState", LobbyPrevState), *GET_ENUM_STRING("EGameState", LobbyCurState));*/
		break;
	}
}

void ASimpleGameGameMode::ChangeState(class UClass* LobbyStateClass)
{
	GameFSM->SetState(LobbyStateClass);
}