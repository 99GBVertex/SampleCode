// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "DesignPattern/FSM.h"
#include "SimpleGameGameMode.generated.h"

UENUM()
enum class EGameState : uint8
{
	NONE		= 0,
	INVENTORY	= 1,
	BATTLEFIELD = 2
};

UCLASS(minimalapi)
class ASimpleGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASimpleGameGameMode();

	virtual void StartPlay() override;
	virtual void Logout(AController* Exiting) override;

	void ChangeStateEnum(EGameState state);

private:
	void ChangeState(class UClass* LobbyStateClass);

private:
	TObjectPtr<UFSM> GameFSM;
	EGameState LobbyCurState;
	EGameState LobbyPrevState;
};



