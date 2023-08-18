// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SimpleUserWidget.h"
#include "Equipment.generated.h"

class UInventoryPage;
class UInventoryItem;
enum class EProductType : uint8;
class USGButton;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UEquipment : public USimpleUserWidget
{
	GENERATED_BODY()

public:
	//~ Begin USimpleUserWidget
	virtual void UIConstuctor() override;
	virtual void UIDestructor() override;
	//~ End USimpleUserWidget

	void SetRoot(const TObjectPtr<UInventoryPage>& InRootPage);
	void SetEquipment();

protected:
	UFUNCTION()
		void OnClieckedEquippedSlot(class UWidget* clickedWidget);

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
	TMap<EProductType, TObjectPtr<UInventoryItem>> EquipTable;
};
