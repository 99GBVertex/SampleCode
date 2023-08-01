// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPage.h"
#include "Components/Button.h"
#include "Manager/NetworkManager.h"
#include "UI/UMG/Item/InventoryItem.h"

void UInventoryPage::NativeConstruct()
{
	Super::NativeConstruct();

	if (TestButton) {
		//TestButton->OnClicked.AddUniqueDynamic(this, &ThisClass::TestNetwork);
	}
}

void UInventoryPage::TestNetwork()
{
	UNetworkManager::Instance()->SendHello();
}
