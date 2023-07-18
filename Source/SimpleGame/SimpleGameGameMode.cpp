// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleGameGameMode.h"
#include "SimpleGamePlayerController.h"
#include "SimpleGameCharacter.h"
#include "UObject/ConstructorHelpers.h"


ASimpleGameGameMode::ASimpleGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASimpleGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/UMG/Common/W_Master"));
	if (WidgetClassFinder.Class != NULL) {
		rootUI = WidgetClassFinder.Class;
	}
}

void ASimpleGameGameMode::StartPlay() {

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), rootUI);
	if (Widget) {
		Widget->AddToViewport();
	}
}