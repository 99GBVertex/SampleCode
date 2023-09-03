// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Item/InventoryList.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/ScrollBox.h"

#include "Manager/ItemManager.h"
#include "Manager/GameEvent/EventType.h"
#include "Manager/GameEvent/EventManager.h"
#include "Misc/SimpleEngineUtil.h"
#include "Character/SwordManCharacter.h"

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
	TArray<TWeakPtr<const FWeapon>> weapons = UItemManager::Instance()->GetWeapons();
	weapons.RemoveAll([](const TWeakPtr<const FWeapon>& row){
		if(!row.IsValid()) return true;
		return row.Pin()->equipState != EEquipState::UNEQUIP;
	});

	for (int i = 0; i < itemPool.Num(); i++) {
		if (IsValid(itemPool[i]->GetItemButton())) {
			itemPool[i]->GetItemButton()->OnClickedReturnSelf.RemoveAll(this);
		}	
	}

	const auto nameSort = [](const TWeakPtr<const FWeapon>& a, const TWeakPtr<const FWeapon>& b) { return b.Pin()->GetName().CompareTo(a.Pin()->GetName()); };
	const auto acquSort = [](const TWeakPtr<const FWeapon>& a, const TWeakPtr<const FWeapon>& b) { return a.Pin()->id == b.Pin()->id ? 0 : a.Pin()->id > b.Pin()->id ? 1 : -1; };
	const auto raritySort = [](const TWeakPtr<const FWeapon>& a, const TWeakPtr<const FWeapon>& b) { return a.Pin()->productData.productGrade == b.Pin()->productData.productGrade ? 0 : a.Pin()->productData.productGrade < b.Pin()->productData.productGrade ? 1 : -1; };
	const auto equipSort = [](const TWeakPtr<const FWeapon>& a, const TWeakPtr<const FWeapon>& b) { return a.Pin()->equipState == b.Pin()->equipState ? 0 : a.Pin()->equipState > b.Pin()->equipState ? 1 : -1; };

	TArray<TFunction<int(const TWeakPtr<const FWeapon>& a, const TWeakPtr<const FWeapon>& b)>> sortSources;
	sortSources = { equipSort, raritySort, acquSort, nameSort };

	const auto combinedLambda = [&sortSources](const TWeakPtr<const FWeapon>& a, const TWeakPtr<const FWeapon>& b)->bool {
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
			currentItem->SetInventoryItem(weapons[i]);
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
	const int poolidx = itemPool.IndexOfByPredicate([clickedWidget](const TObjectPtr<UInventoryItem>& row){
		return row->GetItemButton() == clickedWidget;
	});
	if (poolidx == -1) {
		// log invalid
		return;
	}
	const TWeakPtr<const FItemBase> cachedItem = itemPool[poolidx]->GetCachedItemInfo();
	const bool bUpdatedMount = UItemManager::Instance()->UpdateItemImmediately(cachedItem, EEquipState::EQUIP);
	if (!bUpdatedMount) {
		return;
	}

	if (RootPage) {
		RootPage->InventoryEquipStateChanged(this);
		check(EVENT());
		if(EVENT()) EVENT()->CallEvent(EEventType::msg_rpl_changeequip);
	}

	const TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController();
	if (IsValid(PlayerController))
	{
		const TObjectPtr<ASwordManCharacter> swordMan = Cast<ASwordManCharacter>(PlayerController->GetCharacter());
		if (IsValid(swordMan)) {
			swordMan->AttachWeaponMesh(cachedItem);
		}
	}

#ifdef ADDTOSCREEN_DEBUGMESSAGE
	const FString displayLog = FString::Format(TEXT("{0} {1}"), { cachedItem.Pin()->GetName().ToString(), SIMPLE_LOCSTRING(TEXT("useraction.inventory.mount")) } );	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, displayLog, true, {2.f, 2.f});
#endif
}