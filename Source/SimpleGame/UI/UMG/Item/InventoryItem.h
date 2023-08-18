// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItem.generated.h"

struct FItemBase;
struct FWeapon;
struct FArmor;

class USGButton;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UInventoryItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetInventoryItem(const TWeakPtr<const FItemBase>& InItemData);
	void SetDefault(EProductType pType);
	void SetEmpty();

	TObjectPtr<USGButton> GetItemButton() { return ItemButton; }
	TWeakPtr<const FItemBase> GetCachedItemInfo() { return ButtonCachedItemInfo; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Item", Meta = (BindWidget))
		TObjectPtr<USGButton> ItemButton;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Item", Meta = (BindWidget))
		TObjectPtr<class UImage> Img_Item;

private:
	TWeakPtr<const FItemBase> ButtonCachedItemInfo = nullptr;
};
