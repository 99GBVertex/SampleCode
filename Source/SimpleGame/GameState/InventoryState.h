// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DesignPattern/State.h"
#include "InventoryState.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UInventoryState : public UState
{
public:
	GENERATED_BODY()

	//~ Begin UState
	virtual void StartState() override;
	virtual void EndState() override;
	virtual void RegisterDelegates() override;
	virtual void UnregisterDelegates() override;
	//~ End UState
};