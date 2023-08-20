// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordManCharacter.h"
#include "AI/AISwordMan.h"

// Sets default values
ASwordManCharacter::ASwordManCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASwordManCharacter::BeginPlay()
{
	Super::BeginPlay();


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

