// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SimpleUserWidget.h"
#include "InventoryList.generated.h"

class UUniformGridPanel;
class UInventoryItem;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UInventoryList : public USimpleUserWidget
{
	GENERATED_BODY()

public:
	void SetInventoryList();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", Meta = (BindWidget))
		TObjectPtr<UUniformGridPanel> ItemUniformGridPanel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
		TSubclassOf<UInventoryItem> InventoryItemWidget;

	UPROPERTY()
		TArray<TObjectPtr<UInventoryItem>> itemPool;
};
