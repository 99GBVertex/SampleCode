// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SimpleUserWidget.h"
#include "InventoryPage.generated.h"

class UInventoryItem;
class UButton;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UInventoryPage : public USimpleUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void TestNetwork();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		TObjectPtr<UInventoryItem> EquippedWeapon;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		TObjectPtr<UInventoryItem> EquippedHelmet;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		TObjectPtr<UInventoryItem> EquippedArmor;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		TObjectPtr<UInventoryItem> EquippedGloves;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		TObjectPtr<UInventoryItem> EquippedBoots;

	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		TObjectPtr<UButton> TestButton;
};
