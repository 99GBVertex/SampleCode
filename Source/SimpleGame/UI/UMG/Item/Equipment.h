// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SimpleUserWidget.h"
#include "Equipment.generated.h"

class UInventoryPage;
class UInventoryItem;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UEquipment : public USimpleUserWidget
{
	GENERATED_BODY()

public:
	void SetRoot(const TObjectPtr<UInventoryPage>& InRootPage);
	void SetEquipment();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidget))
		TObjectPtr<UInventoryItem> EquippedWeapon;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidget))
		TObjectPtr<UInventoryItem> EquippedHelmet;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidget))
		TObjectPtr<UInventoryItem> EquippedArmor;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidget))
		TObjectPtr<UInventoryItem> EquippedGloves;
	UPROPERTY(BlueprintReadOnly, Category = "Euipment", Meta = (BindWidget))
		TObjectPtr<UInventoryItem> EquippedBoots;

private:
	UPROPERTY()
		TObjectPtr<UInventoryPage> RootPage;
};
