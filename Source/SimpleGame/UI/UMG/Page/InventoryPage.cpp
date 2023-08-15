// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPage.h"

#include "Manager/NetworkManager.h"

#include "UI/UMG/Item/Equipment.h"
#include "UI/UMG/Item/InventoryList.h"

void UInventoryPage::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryPage::UIConstuctor()
{
	Super::UIConstuctor();
	ResetUIInventoryPage();
}

void UInventoryPage::UIDestructor()
{
	Super::UIDestructor();
}

void UInventoryPage::ResetUIInventoryPage()
{
	if (IsValid(Equipments)) {
		Equipments->SetEquipment();
	}

	if (IsValid(InventoryList)) {
		InventoryList->SetInventoryList();
	}
}

void UInventoryPage::EquipmentEquipStateChanged(const TObjectPtr<UEquipment>& InEquipments)
{
	if (IsValid(InventoryList)) {
		InventoryList->SetInventoryList();
	}
}

void UInventoryPage::InventoryEquipStateChanged(const TObjectPtr<UInventoryList>& InInventory)
{
	if (IsValid(Equipments)) {
		Equipments->SetEquipment();
	}
}
