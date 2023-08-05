// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "State.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SIMPLEGAME_API UState : public UInterface
{
	GENERATED_BODY()

public:

	/**
	 * Bind Functions
	 */
	virtual void RegisterDelegates() {};

	/**
	* Start State
	*/
	virtual void StartState() {};

	/**
	* End State
	*/
	virtual void EndState() {};	

	/**
	 * * UnBind Functions
	 */
	virtual void UnregisterDelegates() {};
};
