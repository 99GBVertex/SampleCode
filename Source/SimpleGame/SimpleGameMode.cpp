// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleGameMode.h"
#include "Misc/SimpleEngineUtil.h"

#include "Manager/NetworkManager.h"
#include "GameState/StartState.h"
#include "GameState/InventoryState.h"
#include "GameState/BattleFieldState.h"

#include "DesignPattern/StateType.h"

ASimpleGameMode::ASimpleGameMode()
{
	
}

void ASimpleGameMode::StartPlay() 
{
	Super::StartPlay();

	SimpleEngineUtil::ModeWorld = GetWorld();
	GameFSM = NewObject<UFSM>(this, TEXT("SimpleGameFSM"));
	if (!IsValid(GameFSM)) {
		Logout(nullptr);
		return;
	}

	FSM_ADDSTATE(GameFSM, UStartState);
	FSM_ADDSTATE(GameFSM, UInventoryState);
	FSM_ADDSTATE(GameFSM, UBattleFieldState);

	ChangeStateEnum(EGameState::START);
}

void ASimpleGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (!IsValid(GameFSM))
	{
		GameFSM->Release();
	}
}

void ASimpleGameMode::ChangeStateEnum(EGameState state)
{
	if (state != EGameState::NONE
		&& state != LobbyCurState)
	{
		LobbyPrevState = LobbyCurState;
		LobbyCurState = state;
	}

	switch (LobbyCurState)
	{
	case EGameState::START:
		ChangeState(UStartState::StaticClass());
		break;
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

void ASimpleGameMode::ChangeState(class UClass* LobbyStateClass)
{
	GameFSM->SetState(LobbyStateClass);
}