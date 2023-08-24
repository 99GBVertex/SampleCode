// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "SwordManCharacter.generated.h"

class UAISwordMan;
class UFSM;

UCLASS()
class SIMPLEGAME_API ASwordManCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASwordManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void InitFSM() override;

	void InitAnimInstance();

public:
	TObjectPtr<UAISwordMan> GetAI() { return SwordManAI; }

private:
	UPROPERTY(VisibleAnywhere, Category = "SwordManCharacter")
		USkeletalMeshComponent* SwordManSKMesh;
	UPROPERTY(VisibleAnywhere, Category = "SwordManCharacter")
		TObjectPtr<UAISwordMan> SwordManAI;			

	UPROPERTY(VisibleAnywhere, Category = "SwordManCharacter")
		TObjectPtr<USceneComponent> HandL;
	UPROPERTY(VisibleAnywhere, Category = "SwordManCharacter")
		TObjectPtr<USceneComponent> HandR;
};
