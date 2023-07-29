// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPage.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UInventoryPage : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		class UInventoryItem* EquippedWeapon;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		class UInventoryItem* EquippedHelmet;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		class UInventoryItem* EquippedArmor;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		class UInventoryItem* EquippedGloves;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidgetOptional))
		class UInventoryItem* EquippedBoots;

public:
	virtual bool Initialize() override;
	
};
