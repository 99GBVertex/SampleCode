// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleGameGameMode.h"
#include "UObject/ConstructorHelpers.h"


ASimpleGameGameMode::ASimpleGameGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/UMG/Common/W_Master"));
	if (WidgetClassFinder.Class != NULL) {
		rootUI = WidgetClassFinder.Class;
	}
}

void ASimpleGameGameMode::StartPlay() 
{
	Super::StartPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), rootUI);
	if (Widget) {
		Widget->AddToViewport();
	}
}