// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DesignPattern/State.h"
#include "BattleFieldState.generated.h"

UCLASS()
class SIMPLEGAME_API UBattleFieldState : public UState
{
public:
	GENERATED_BODY()

	//~ Begin UState
	virtual void RegisterDelegates() override;
	virtual void StartState() override;
	virtual void EndState() override;
	virtual void UnregisterDelegates() override;
	//~ End UState
};
