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
	if (IsValid(Equipments)) {

	}

	if (IsValid(InventoryList)) {
		InventoryList->SetInventoryList();
	}
}

void UInventoryPage::UIDestructor()
{
	Super::UIDestructor();
}
