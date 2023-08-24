// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/State/CharacterStateDefine.h"
#include "AISwordMan.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UAISwordMan : public UAnimInstance
{
	GENERATED_BODY()

public:
	void Init();
	void Release();

	ECharacterState GetCurrentCharState() { return CurrentCharacterAnimState; }
	void SetCurrentCharState(ECharacterState InCharState) { CurrentCharacterAnimState = InCharState; }

public:
	UFUNCTION(BlueprintNativeEvent)
		void SG_Idle_ChangeWeapon();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SwordMan", meta = (AllowPrivateAccess = "true"))
		ECharacterState CurrentCharacterAnimState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SwordMan Flags", meta = (AllowPrivateAccess = "true"))
		float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SwordMan Flags", meta = (AllowPrivateAccess = "true"))
		bool bMontaging;
};
