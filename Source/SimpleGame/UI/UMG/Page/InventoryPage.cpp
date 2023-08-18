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
	InitUIInventoryPage();
}

void UInventoryPage::UIDestructor()
{
	Super::UIDestructor();
}

void UInventoryPage::InitUIInventoryPage()
{
	if (IsValid(Equipments)) {
		Equipments->UIConstuctor();
		Equipments->SetEquipment();
		Equipments->SetRoot(this);
	}
	if (IsValid(InventoryList)) {
		InventoryList->UIConstuctor();
		InventoryList->SetInventoryList();
		InventoryList->SetRoot(this);
	}
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
	ResetUIInventoryPage();
}

void UInventoryPage::InventoryEquipStateChanged(const TObjectPtr<UInventoryList>& InInventory)
{
	ResetUIInventoryPage();
}
