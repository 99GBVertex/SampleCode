// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.generated.h"

struct FItemBase;
struct FWeapon;
struct FArmor;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UInventoryItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetInventoryItem(const TWeakPtr<FItemBase>& itemData);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Item", Meta = (BindWidget))
		TObjectPtr<class UButton> ItemButton;
};
