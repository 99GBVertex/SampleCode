// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Define.h"
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
	void SetDefault(EProductType pType);
	void SetEmpty();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Item", Meta = (BindWidget))
		TObjectPtr<class UButton> ItemButton;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Item", Meta = (BindWidget))
		TObjectPtr<class UImage> Img_Item;
};
