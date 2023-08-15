// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SimpleUserWidget.h"
#include "InventoryList.generated.h"

class UUniformGridPanel;
class UScrollBox;
class UInventoryPage;
class UInventoryItem;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UInventoryList : public USimpleUserWidget
{
	GENERATED_BODY()

public:
	void SetRoot(const TObjectPtr<UInventoryPage>& InRootPage);
	void SetInventoryList();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", Meta = (BindWidget))
		TObjectPtr<UUniformGridPanel> ItemUniformGridPanel;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", Meta = (BindWidget))
		TObjectPtr<UScrollBox> ItemScrollBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
		TSubclassOf<UInventoryItem> InventoryItemWidget;

	UFUNCTION()
		void OnMount(UWidget* clickedWidget);
private:
	UPROPERTY()
		TObjectPtr<UInventoryPage> RootPage;
	UPROPERTY()
		TArray<TObjectPtr<UInventoryItem>> itemPool;

	const int32 kSlotCount = 4;

};
