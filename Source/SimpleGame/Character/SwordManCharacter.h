// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "SwordManCharacter.generated.h"

class UAISwordMan;
class UFSM;
class UArrowComponent;
struct FItemBase;
struct FWeapon;
struct FArmor;

UCLASS()
class SIMPLEGAME_API ASwordManCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASwordManCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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

	void AttachWeaponMesh(const TWeakPtr<const FItemBase> targetWeapon);
	void DetachWeaponMesh();
protected:
	void AttachWeaponMesh(int32 itemIndex);

private:
	UPROPERTY(VisibleAnywhere, Category = "SwordManCharacter")
		TObjectPtr<USkeletalMeshComponent> SwordManSKMesh;
	UPROPERTY(VisibleAnywhere, Category = "SwordManCharacter")
		TObjectPtr<UAISwordMan> SwordManAI;			

	UPROPERTY(VisibleAnywhere, Category = "SwordManCharacter")
		TObjectPtr<UArrowComponent> IKHandL;
	UPROPERTY(VisibleAnywhere, Category = "SwordManCharacter")
		TObjectPtr<UArrowComponent> IKHandR;

	UPROPERTY(VisibleAnywhere, Category = "SwordManCharacter")
		TObjectPtr<UStaticMeshComponent> IKWeaponPointL;
	UPROPERTY(VisibleAnywhere, Category = "SwordManCharacter")
		TObjectPtr<UStaticMeshComponent> IKWeaponPointR;
};
