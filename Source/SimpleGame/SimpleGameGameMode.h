// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "SimpleGameGameMode.generated.h"

UCLASS(minimalapi)
class ASimpleGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASimpleGameGameMode();

	virtual void StartPlay() override;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> rootUI;
};



