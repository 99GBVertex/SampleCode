// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateType.generated.h"

UENUM()
enum class EGameState : uint8
{
	NONE = 0,
	START = 10,
	INVENTORY = 20,
	BATTLEFIELD = 30
};
