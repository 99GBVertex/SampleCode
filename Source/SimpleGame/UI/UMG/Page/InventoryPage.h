// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SimpleMsgUserWidget.h"
#include "InventoryPage.generated.h"

class UEquipment;
class UInventoryList;

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UInventoryPage : public USimpleMsgUserWidget
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

	//~ Begin USimpleUserWidget
	virtual void BindEventCalls() override;
	virtual void OnBoundEventBroadCast(EEventType eventType, EventMsgPtr message) override;
	virtual void UnBindEventCalls() override;
	//~ End USimpleUserWidget

public:
	void InitUIInventoryPage();
	void ResetUIInventoryPage();
	void EquipmentEquipStateChanged(const TObjectPtr<UEquipment>& InEquipments);
	void InventoryEquipStateChanged(const TObjectPtr<UInventoryList>& InInventory);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Equipment Base", Meta = (BindWidget))
		TObjectPtr<UEquipment> Equipments;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Base", Meta = (BindWidget))
		TObjectPtr<UInventoryList> InventoryList;
};
