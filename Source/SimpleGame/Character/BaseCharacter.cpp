// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/SceneComponent.h"
#include "DesignPattern/FSM.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

		CharacterFSM = NewObject<UFSM>(this, TEXT("CharacterFSM"));
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::OnCharacterStateChanged(const UClass* Class)
{
	if (IsValid(CharacterFSM))
		CharacterFSM->SetState(Class);
}

void ABaseCharacter::InitFSM()
{
	this->OnStateChanged.AddUObject(this, &ThisClass::OnCharacterStateChanged);
}
