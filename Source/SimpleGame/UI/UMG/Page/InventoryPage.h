// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SimpleUserWidget.h"
#include "InventoryPage.generated.h"

class UEquipment;
class UInventoryList;

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UInventoryPage : public USimpleUserWidget
{
	GENERATED_BODY()

public:
	//~ Begin UUSserWidget
	virtual void NativeConstruct() override;
	//~ End UUSserWidget

	//~ Begin USimpleUserWidget
	virtual void UIConstuctor() override;
	virtual void UIDestructor() override;
	//~ End USimpleUserWidget

public:
	void ResetUIInventoryPage();
	void EquipmentEquipStateChanged(const TObjectPtr<UEquipment>& InEquipments);
	void InventoryEquipStateChanged(const TObjectPtr<UInventoryList>& InInventory);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Equipment Base", Meta = (BindWidget))
		TObjectPtr<UEquipment> Equipments;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Base", Meta = (BindWidget))
		TObjectPtr<UInventoryList> InventoryList;
};
