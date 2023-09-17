// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/SceneComponent.h"
#include "DesignPattern/FSM.h"

// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		//CharacterRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
		//CharacterRoot->SetupAttachment(RootComponent);
		//CharacterRoot->SetupAttachment(GetMesh());
		CharacterFSM = NewObject<UFSM>(this, TEXT("CharacterFSM"));
	}
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitFSM();

#if WITH_EDITOR || PLATFORM_WINDOWS
	InputComponent->BindAction("LeftMouse", IE_Released, this, &ThisClass::MouseReleased);
#elif PLATFORM_IOS || PLATFORM_ANDROID
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &ThisClass::InputReleased);
#endif
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

void ABaseCharacter::InputReleased(ETouchIndex::Type FingerIndex, FVector location)
{
	if (FingerIndex == ETouchIndex::Type::Touch1) {
		MouseReleased();
	}
}

void ABaseCharacter::MouseReleased()
{
	EVENT()->CallEvent(EEventType::msg_input_release_nonui);
}
