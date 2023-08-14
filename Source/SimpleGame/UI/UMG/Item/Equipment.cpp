// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Item/Equipment.h"
#include "UI/UMG/Item/InventoryItem.h"

void UEquipment::SetEquipment()
{
	if (EquippedWeapon) EquippedWeapon->SetDefault(EProductType::WEAPON);
	if (EquippedHelmet) EquippedHelmet->SetDefault(EProductType::HELMET);
	if (EquippedArmor)	EquippedArmor->SetDefault(EProductType::ARMOR);
	if (EquippedGloves) EquippedGloves->SetDefault(EProductType::GLOVES);
	if (EquippedBoots)  EquippedBoots->SetDefault(EProductType::BOOTS);
}

