// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordManCharacter.h"

#include "Components/SkeletalMeshComponent.h"

#include "DesignPattern/FSM.h"
#include "AI/AISwordMan.h"

#include "Character/State/SwordManState_Idle.h"

// Sets default values
ASwordManCharacter::ASwordManCharacter()
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		PrimaryActorTick.bCanEverTick = true;
		PrimaryActorTick.bStartWithTickEnabled = true;

		HandL = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHand"));
		HandL->SetupAttachment(RootComponent);

		HandR = CreateDefaultSubobject<USceneComponent>(TEXT("RightHand"));
		HandR->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void ASwordManCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitFSM();
	InitAnimInstance();
}

// Called every frame
void ASwordManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASwordManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASwordManCharacter::InitFSM()
{
	Super::InitFSM();

	FSM_ADDSTATE(CharacterFSM, USwordManState_Idle);
	this->OnStateChanged.Broadcast(USwordManState_Idle::StaticClass());
}

void ASwordManCharacter::InitAnimInstance()
{
	if (!RootComponent) {
		// log Init Error
		return;
	}
	SwordManSKMesh = GetMesh();
	ensure(IsValid(SwordManSKMesh));

	SwordManAI = Cast<UAISwordMan>(SwordManSKMesh->GetAnimInstance());
	ensure(IsValid(SwordManAI));

	SwordManAI->Init();
}

