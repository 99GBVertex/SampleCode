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
	UPROPERTY(BlueprintReadWrite, Category = "Equipped")
		class UInventoryItem* EquippedWeapon;
	UPROPERTY(BlueprintReadWrite, Category = "Equipped")
		class UInventoryItem* EquippedTorsor;
	UPROPERTY(BlueprintReadWrite, Category = "Equipped")
		class UInventoryItem* EquippedPants;
	UPROPERTY(BlueprintReadWrite, Category = "Equipped")
		class UInventoryItem* EquippedGloves;
	UPROPERTY(BlueprintReadWrite, Category = "Equipped")
		class UInventoryItem* EquippedShoes;

public:
	virtual bool Initialize() override;
	
};
