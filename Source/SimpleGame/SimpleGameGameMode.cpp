// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleGameGameMode.h"
#include "Misc/SimpleEngineUtil.h"

#include "GameState/BattleFieldState.h"
#include "GameState/InventoryState.h"

ASimpleGameGameMode::ASimpleGameGameMode()
{
	
}

void ASimpleGameGameMode::StartPlay() 
{
	Super::StartPlay();

	SimpleEngineUtil::ModeWorld = GetWorld();
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