// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Item/InventoryList.h"
#include "Components/UniformGridPanel.h"
#include "Manager/ItemManager.h"
#include "UI/UMG/Item/InventoryItem.h"

void UInventoryList::SetInventoryList()
{
	TArray<TWeakPtr<FWeapon>> weapons = UItemManager::Instance()->GetWeapons();
	for (int i = 0; i < itemPool.Num(); i++) {
		//itemPool[i]->OnClickedWith.RemoveAll(this);
	}

	//int64 curSelectSlotBagID = -1;
	//TArray<FU2CaddieBag*> slotInBags = UU2InventoryManager::Instance()->GetSIotInCaddieBags();
	//int idx = slotInBags.IndexOfByPredicate([curBagSlotOrder](FU2CaddieBag* row) {
	//	return row->bagSlotOrder == curBagSlotOrder;
	//	});
	//if (idx != -1) {
	//	curSelectSlotBagID = slotInBags[idx]->bagId;
	//}

	//TMap<int32, uint8> bagSlotIdxTable{ {0, 0} };
	//for (FU2CaddieBag* curBag : UU2InventoryManager::Instance()->GetSIotInCaddieBags()) {
	//	bagSlotIdxTable.Emplace(curBag->bagId, ConvertToBagSlotIndex(curBag->bagSlotOrder));
	//}

	//TArray<const FU2Consumable*> invenConsumables = UU2InventoryManager::Instance()->GetInventoryConsumables();
	//TArray<const FU2Consumable*> equipConsumables = UU2InventoryManager::Instance()->GetEquippedConsumables();

	//auto nameSort = [](const FU2Consumable& a, const FU2Consumable& b) { return b.GetName().CompareTo(a.GetName()); };
	//auto acquSort = [](const FU2Consumable& a, const FU2Consumable& b) { return a.id == b.id ? 0 : a.id > b.id ? 1 : -1; };
	//auto raritySort = [](const FU2Consumable& a, const FU2Consumable& b) { return a.productData.ProductClass == b.productData.ProductClass ? 0 : a.productData.ProductClass < b.productData.ProductClass ? 1 : -1; };
	//auto newSort = [](const FU2Consumable& a, const FU2Consumable& b) { return a.noticeType == b.noticeType ? 0 : a.noticeType < b.noticeType ? 1 : -1; };
	//auto equipSort = [](const FU2Consumable& a, const FU2Consumable& b) { return a.installType == b.installType ? 0 : a.installType > b.installType ? 1 : -1; };
	//auto bagSlotSort = [curSelectSlotBagID](const FU2Consumable& a, const FU2Consumable& b) { if (a.bagId == curSelectSlotBagID && b.bagId != curSelectSlotBagID)	return 1;
	//else if (a.bagId != curSelectSlotBagID && b.bagId == curSelectSlotBagID)	return -1;
	//else return 0; };

	//TArray<TFunction<int(const FU2Consumable& a, const FU2Consumable& b)>> sortSources;
	//switch (sortType)
	//{
	//default:
	//case EInventorySortType::RARITY:	sortSources = { equipSort,	bagSlotSort,	raritySort,	newSort,	acquSort,	nameSort }; break;
	//case EInventorySortType::ACQUIRE:	sortSources = { equipSort,	bagSlotSort,	acquSort,	raritySort,	newSort,	nameSort }; break;
	//case EInventorySortType::NAME:		sortSources = { equipSort,	bagSlotSort,	nameSort,	raritySort,	newSort,	acquSort }; break;
	//}

	//auto combinedLambda = [&](const FU2Consumable& a, const FU2Consumable& b)->bool {
	//	int result = 0;
	//	for (auto it : sortSources) {
	//		if (it(a, b) != 0 || &it == &sortSources.Last()) {
	//			result = it(a, b);
	//			break;
	//		}
	//	}
	//	return result == 1 ? true : false;
	//};
	//invenConsumables.Sort(combinedLambda);

	//// Ä­º¸Á¤
	///*int variableInvenCount = slotCount * kDefault_ClubPittingPage_InvenRowCount;
	//int inventorySize = FMath::Max<int>(variableInvenCount, invenConsumables.Num());
	//inventorySize += (slotCount - inventorySize % slotCount);*/
	//int inventorySize = invenConsumables.Num();

	//int uiCnt = 0;
	//for (int i = 0; i < inventorySize; i++)
	//{
	//	if (uiCnt < GetClubNum())
	//	{
	//		UWidget* child = ClubInventoryScroll->GetChildAt(uiCnt);
	//		CurrentItem = (UU2ClubInventoryItem*)child;
	//	}
	//	else
	//	{
	//		CurrentItem = CreateWidget<UU2ClubInventoryItem>(ClubInventoryScroll, clubInvenItem);
	//		ClubInventoryScroll->AddChildToUniformGrid(CurrentItem);
	//	}

	//	if (CurrentItem == nullptr)
	//		continue;
	//	UUniformGridSlot* slot = Cast<UUniformGridSlot>(CurrentItem->Slot);
	//	if (slot) {
	//		slot->SetRow(uiCnt / slotCount);
	//		slot->SetColumn(uiCnt % slotCount);
	//		slot->HorizontalAlignment = EHorizontalAlignment::HAlign_Fill;
	//		slot->SynchronizeProperties();
	//	}
	//	++uiCnt;
	//	CurrentItem->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	//	if (i < invenConsumables.Num())
	//	{
	//		const FU2Consumable* curConsumableInfo = invenConsumables[i];

	//		CurrentItem->SetConsumable(curConsumableInfo);
	//		bool bMark = curConsumableInfo->installType == EInstallType::Equip ? true : false;
	//		bool bMarkEnable = curSelectSlotBagID == curConsumableInfo->bagId;
	//		int bagSlotIndex = bagSlotIdxTable.Contains(curConsumableInfo->bagId) ? bagSlotIdxTable[curConsumableInfo->bagId] : -1;
	//		CurrentItem->SetMountingMark(bagSlotIndex, bMark, bMarkEnable);
	//		CurrentItem->SetEnhanceCheck(false);
	//		CurrentItem->OnClickedWith.AddUniqueDynamic(this, &ThisClass::OnClickConsumableItem);
	//		inventoryItems.Emplace(CurrentItem);
	//	}
	//}

	////uiCnt += uiCnt % slotCount;
	//for (int i = invenConsumables.Num(); i < GetClubNum(); i++)
	//{
	//	UU2ClubInventoryItem* currentItem;
	//	UWidget* child = ClubInventoryScroll->GetChildAt(i);
	//	if (child == nullptr)
	//		continue;

	//	currentItem = (UU2ClubInventoryItem*)child;
	//	currentItem->SetEmpty();
	//	if (i >= uiCnt)
	//		currentItem->SetVisibility(ESlateVisibility::Collapsed);
	//}

	//ScrollBox->ScrollToStart();
	//ScrollBox->EndInertialScrolling();

	//UU2InventoryManager::Instance()->ReadNotificationConsumableInventory();

	//for (UU2ClubInventoryItem* it : inventoryItems) {
	//	if (it->Icon_New->IsVisible()) {
	//		it->NewLoopAnimRestart();
	//	}
	//}
}


