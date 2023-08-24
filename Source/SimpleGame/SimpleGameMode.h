// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "DesignPattern/FSM.h"
#include "SimpleGameMode.generated.h"

enum class EGameState : uint8;

UCLASS(minimalapi)
class ASimpleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASimpleGameMode();

	virtual void StartPlay() override;
	virtual void Logout(AController* Exiting) override;

	void ChangeStateEnum(EGameState state);

private:
	void ChangeState(class UClass* LobbyStateClass);

private:
	UPROPERTY() TObjectPtr<UFSM> GameFSM;
	EGameState LobbyCurState;
	EGameState LobbyPrevState;
};



