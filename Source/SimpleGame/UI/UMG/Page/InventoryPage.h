// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPage.generated.h"

class UInventoryItem;
class UButton;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UInventoryPage : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void TestNetwork();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		UInventoryItem* EquippedWeapon;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		UInventoryItem* EquippedHelmet;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		UInventoryItem* EquippedArmor;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		UInventoryItem* EquippedGloves;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		UInventoryItem* EquippedBoots;

	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		UButton* TestButton;	
};
