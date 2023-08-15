// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Item/Equipment.h"
#include "UI/UMG/Page/InventoryPage.h"
#include "UI/UMG/Item/InventoryItem.h"

void UEquipment::SetRoot(const TObjectPtr<UInventoryPage>& InRootPage)
{
	RootPage = InRootPage;
}

void UEquipment::SetEquipment()
{
	if (IsValid(EquippedWeapon)) EquippedWeapon->SetDefault(EProductType::WEAPON);
	if (IsValid(EquippedHelmet)) EquippedHelmet->SetDefault(EProductType::HELMET);
	if (IsValid(EquippedArmor))	 EquippedArmor->SetDefault(EProductType::ARMOR);
	if (IsValid(EquippedGloves)) EquippedGloves->SetDefault(EProductType::GLOVES);
	if (IsValid(EquippedBoots))  EquippedBoots->SetDefault(EProductType::BOOTS);
}

