// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DesignPattern/State.h"
#include "CharacterStateDefine.h"
#include "Character/SwordManCharacter.h"
#include "SwordManState_Base.generated.h"

UCLASS()
class SIMPLEGAME_API USwordManState_Base : public UState
{
	GENERATED_BODY()

public:
	USwordManState_Base();
	virtual ~USwordManState_Base() {};

protected:
	UPROPERTY()
		TObjectPtr<ASwordManCharacter> SwordManCharacter;
	UPROPERTY()
		ECharacterState CharacterAnimState;
};