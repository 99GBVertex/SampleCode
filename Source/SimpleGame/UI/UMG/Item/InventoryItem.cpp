// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

#include "Components/Image.h"

#include "Misc/SimpleEngineUtil.h"
#include "Manager/ItemStruct.h"

#include "UI/UMG/Provider/ResourceProvider.h"
#include "UI/UMG/SGButton.h"

void UInventoryItem::SetInventoryItem(const TWeakPtr<FItemBase>& itemData)
{
	if(!itemData.IsValid()) {
		SetEmpty();
		return;
	}
	const FItemBase* curItem = itemData.Pin().Get();
	if(IsValid(Img_Item)) {
		Img_Item->SetBrushResourceObject(curItem->resourceData.sprite_Optr.LoadSynchronous());
	}
	if (IsValid(ItemButton)) {
		ItemButton->SetIsEnabled(true);
	}
}

void UInventoryItem::SetDefault(EProductType pType)
{
	if (IsValid(Img_Item)) {
		Img_Item->SetBrushResourceObject(RESOURCE()->GetTypeDefaultUI(pType).LoadSynchronous());
	}
	if (IsValid(ItemButton)) {
		ItemButton->SetIsEnabled(false);
	}
}

void UInventoryItem::SetEmpty()
{
	//ItemButton
	if (IsValid(Img_Item)) {
		Img_Item->ReleaseSlateResources(true);
	}
}
