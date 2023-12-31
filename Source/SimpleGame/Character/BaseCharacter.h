// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterStateChanged, const UClass* /*Class*/);

class UFSM;

UCLASS()
class SIMPLEGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// need interface?
	UFUNCTION() void OnCharacterStateChanged(const UClass* Class);
	virtual void InitFSM();

	void InputReleased(ETouchIndex::Type FingerIndex, FVector location);
	void MouseReleased();

protected:
	UPROPERTY() TObjectPtr<UFSM> CharacterFSM;
	FCharacterStateChanged OnStateChanged;

	UPROPERTY(VisibleAnywhere, Category = "BaseCharacter")
		TObjectPtr<USceneComponent> CharacterRoot;
};
