// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MasterWidget.generated.h"

enum class EUIType : uint8;
class UOverlay;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UMasterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Layer")
		TObjectPtr<UOverlay> Page;
	UPROPERTY(BlueprintReadOnly, Category = "Layer")
		TObjectPtr<UOverlay> Popup;
	UPROPERTY(BlueprintReadOnly, Category = "Layer")
		TObjectPtr<UOverlay> SystemPopup;

public:
	TObjectPtr<UWidget> GetTypeRoot(EUIType InUIType);
};
