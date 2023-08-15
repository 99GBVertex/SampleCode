// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Item/InventoryList.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/ScrollBox.h"

#include "Manager/ItemManager.h"

#include "UI/UMG/Page/InventoryPage.h"
#include "UI/UMG/Item/InventoryItem.h"
#include "UI/UMG/SGButton.h"


void UInventoryList::SetRoot(const TObjectPtr<UInventoryPage>& InRootPage)
{
	RootPage = InRootPage;
}

void UInventoryList::SetInventoryList()
{
	// weapons
	TArray<TWeakPtr<FWeapon>> weapons = UItemManager::Instance()->GetWeapons();
	weapons.RemoveAll([](const TWeakPtr<FWeapon>& row){
		return !row.IsValid();
	});

	for (int i = 0; i < itemPool.Num(); i++) {
		//itemPool[i]->OnClickedWith.RemoveAll(this);
	}
	auto nameSort = [](const TWeakPtr<FWeapon>& a, const TWeakPtr<FWeapon>& b) { return b.Pin()->GetName().CompareTo(a.Pin()->GetName()); };
	auto acquSort = [](const TWeakPtr<FWeapon>& a, const TWeakPtr<FWeapon>& b) { return a.Pin()->id == b.Pin()->id ? 0 : a.Pin()->id > b.Pin()->id ? 1 : -1; };
	auto raritySort = [](const TWeakPtr<FWeapon>& a, const TWeakPtr<FWeapon>& b) { return a.Pin()->productData.productGrade == b.Pin()->productData.productGrade ? 0 : a.Pin()->productData.productGrade < b.Pin()->productData.productGrade ? 1 : -1; };
	auto equipSort = [](const TWeakPtr<FWeapon>& a, const TWeakPtr<FWeapon>& b) { return a.Pin()->equipState == b.Pin()->equipState ? 0 : a.Pin()->equipState > b.Pin()->equipState ? 1 : -1; };

	TArray<TFunction<int(const TWeakPtr<FWeapon>& a, const TWeakPtr<FWeapon>& b)>> sortSources;
	sortSources = { equipSort, raritySort, acquSort, nameSort };

	auto combinedLambda = [&](const TWeakPtr<FWeapon>& a, const TWeakPtr<FWeapon>& b)->bool {
		int result = 0;
		for (auto it : sortSources) {
			if (it(a, b) != 0 || &it == &sortSources.Last()) {
				result = it(a, b);
				break;
			}
		}
		return result == 1 ? true : false;
	};
	weapons.Sort(combinedLambda);
	
	int uiCnt = 0;
	TObjectPtr<UInventoryItem> currentItem = nullptr;
	for (int i = 0; i < weapons.Num(); i++)
	{
		if (uiCnt < ItemUniformGridPanel->GetChildrenCount())
		{
			TObjectPtr<UWidget> child = ItemUniformGridPanel->GetChildAt(uiCnt);
			currentItem = Cast<UInventoryItem>(child);
		}
		else
		{
			currentItem = CreateWidget<UInventoryItem>(ItemUniformGridPanel, InventoryItemWidget);
			ItemUniformGridPanel->AddChildToUniformGrid(currentItem);
		}

		if (!IsValid(currentItem)) {
			continue;
		}

		TObjectPtr<UUniformGridSlot> slot = Cast<UUniformGridSlot>(currentItem->Slot);
		if (IsValid(slot)) {
			slot->SetRow(uiCnt / kSlotCount);
			slot->SetColumn(uiCnt % kSlotCount);
			slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			slot->SynchronizeProperties();
		}
		++uiCnt;
		currentItem->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		if (i < weapons.Num() && weapons[i].IsValid())
		{
			TWeakPtr<FWeapon> curItemInfo = weapons[i];

			currentItem->SetInventoryItem(curItemInfo);
			TObjectPtr<USGButton> currentItemButton = currentItem->GetItemButton();
			if (IsValid(currentItemButton)) 
			{
				if (!currentItemButton->OnClickedReturnSelf.Contains(this, "OnMount")) {
					currentItemButton->OnClickedReturnSelf.AddUniqueDynamic(this, &ThisClass::OnMount);
				}
			}
			itemPool.Emplace(currentItem);
		}
	}

	for (int i = uiCnt; i < ItemUniformGridPanel->GetChildrenCount(); i++)
	{		
		TObjectPtr<UWidget> child = ItemUniformGridPanel->GetChildAt(i);
		if (!IsValid(child) || !child->IsA<UInventoryItem>())
			continue;
		currentItem = Cast<UInventoryItem>(child);
		currentItem->SetEmpty();
		currentItem->SetVisibility(ESlateVisibility::Collapsed);	
	}

	ItemScrollBox->ScrollToStart();
	ItemScrollBox->EndInertialScrolling();
}

void UInventoryList::OnMount(UWidget* clickedWidget)
{
	//Call UpdateItemImmediately();
}


