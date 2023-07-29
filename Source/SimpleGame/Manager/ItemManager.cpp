// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"
#include "PaperSpriteAtlas.h"
#include "Manager/DBManager.h"


void FItemBase::SetTableKey()
{
	nameTableKey = FString::Format(TEXT("Item.{0}.name"), { index });
	descriptTableKey = FString::Format(TEXT("Item.{0}.description"), { index });
}

bool FItemBase::IsExpired() const
{
	if (productData.productSection == EProductSection::EXPIRABLE) {
		const int64 expireTick = FDateTime(expireDate).GetTicks();
		const int64 utcNowTick = FDateTime::UtcNow().GetTicks();
		const bool expired = (expireTick - utcNowTick) <= 0;
		return expired;
	}
	return false;
}

bool FItemBase::IsValid() const
{
	// As DEFAULT_ALIGNMENT is defined to 0 now, I changed that to the original numerical value here
	const int32 AlignmentCheck = MIN_ALIGNMENT - 1;

	// Check 'this' pointer before trying to access any of the Object's members
	if ((this == nullptr) || (UPTRINT)this < 0x100)
	{
		UE_LOG(LogTemp, Error, TEXT("\'this\' pointer is invalid."));
		return false;
	}
	if ((UPTRINT)this & AlignmentCheck)
	{
		UE_LOG(LogTemp, Error, TEXT("\'this\' pointer is misaligned."));
		return false;
	}
	if (*(void**)this == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Virtual functions table is invalid."));
		return false;
	}

	if (id <= 0 || index <= 0) {
		UE_LOG(LogTemp, Error, TEXT("ItemID or Index is invalid."));
		return false;
	}
	return true;
}

TArray<const FAttributeInfo*> FItemBase::GetAttributes() const
{
	TArray<const FAttributeInfo*> outAtts;
	if (attributeList.Num() <= 0) return outAtts;

	for (TSharedPtr<FAttributeInfo> setAttribute : attributeList) {
		if (!setAttribute.IsValid()) continue;
		outAtts.Emplace(setAttribute.Get());
	}
	return outAtts;
}

void UItemManager::Init()
{
	Weapons.Empty();
	Armors.Empty();
	equipmentSlots.Empty();

	Weapons.Reserve(kDefaultWeaponInventorySize);
	Armors.Reserve(kDefaultArmorInventorySize);
}

void UItemManager::Release()
{
}

void UItemManager::MakeItemDataTable()
{
	TArray<FItemTable*> tempItemTable;
	UDBManager::Instance()->GetDataTableRows<FItemTable>(TEXT("ItemTable"), tempItemTable);

	ItemTable.Empty();	
	for (const FItemTable* row : tempItemTable) {
		FItemTable copyRow;
		copyRow.index				= row->index;
		copyRow.item_mesh_Optr		= row->item_mesh_Optr;
		copyRow.item_sprite_Optr	= row->item_sprite_Optr;
		ItemTable.Emplace(MoveTemp(copyRow));
	}	
}

FItemTable* UItemManager::GetItemData(int32 inIndex)
{
	return ItemTable.FindByPredicate([inIndex](const FItemTable& row) {
		return row.index == inIndex;
	});
}

void UItemManager::BindInventoryData(TArray<NetItemData*>& netItems, TArray<NetAttributeData*>& netAtts)
{
	for (const NetItemData* netItem : netItems) {
		FItemTable* curItem = GetItemData(netItem->Index);
		if (!curItem) {
			continue;
		}

		EProductType itemType = curItem->itemType;
		switch (itemType)
		{
		case EProductType::WEAPON:
			//Weapons.Emplace();
			break;
		case EProductType::ARMOR:		[[fallthrough]];			
		case EProductType::HELMET:		[[fallthrough]];
		case EProductType::GLOVES:		[[fallthrough]];
		case EProductType::BOOTS:
			//Armors.Emplace();
			break;
		case EProductType::CONSUMABLE:	[[fallthrough]];
		case EProductType::QUESTITEM:	[[fallthrough]];
		case EProductType::NONE:		[[fallthrough]];
		default:
			break;
		}
	}
}
