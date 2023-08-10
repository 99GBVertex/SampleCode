// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"
#include "PaperSpriteAtlas.h"
#include "Manager/DBManager.h"

void FItemBase::BindNetData(const NetItemData& InNetData)
{
	id = InNetData.ID;
	expireDate = InNetData.ExpireDate;
}

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
		copyRow.itemSection			= row->itemSection;
		copyRow.itemType			= row->itemType;
		copyRow.item_mesh_Optr		= row->item_mesh_Optr;
		copyRow.item_sprite_Optr	= row->item_sprite_Optr;
		ItemTable.Emplace(MoveTemp(copyRow));
	}
}

const FItemTable* UItemManager::GetItemData(int32 inIndex)
{
	return ItemTable.FindByPredicate([inIndex](const FItemTable& row) {
		return row.index == inIndex;
	});
}

bool UItemManager::CreateWeapon(int32 inIndex, TSharedPtr<FWeapon>& outWeapon)
{
	const FItemTable* curItem = GetItemData(inIndex);
	if (!curItem) {
		return false;
	}
	if (!outWeapon || !outWeapon.IsValid()) {
		outWeapon = MakeShared<FWeapon>();
	}
	outWeapon->index = inIndex;
	outWeapon->productData.productSection = curItem->itemSection;
	outWeapon->productData.productType = curItem->itemType;

	outWeapon->SetTableKey();
	return true;
}

bool UItemManager::CreateArmor(int32 inIndex, TSharedPtr<FArmor>& outArmor)
{
	const FItemTable* curItem = GetItemData(inIndex);
	if (!curItem) {
		return false;
	}
	if (!outArmor || !outArmor.IsValid()) {
		outArmor = MakeShared<FArmor>();
	}
	outArmor->index = inIndex;
	outArmor->productData.productSection = curItem->itemSection;
	outArmor->productData.productType = curItem->itemType;

	outArmor->SetTableKey();
	return true;
}

void UItemManager::BindInventoryData(const TArray<NetItemData>& netItems, const TArray<NetAttributeData>& netAtts)
{
	for (const NetItemData& netItem : netItems) {
		if (netItem.ID == 0 || netItem.Index == 0) {
			continue;
		}			
		const FItemTable* curItem = GetItemData(netItem.Index);
		if (!curItem) {
			continue;
		}
		EProductType itemType = curItem->itemType;
		switch (itemType)
		{
		case EProductType::WEAPON:
		{
			TSharedPtr<FWeapon> curWeapon;
			int weaponIdx = Weapons.IndexOfByPredicate([netItem](const TSharedPtr<FWeapon>& row) {
				return row->id == netItem.ID;
				});
			if (weaponIdx == -1) {
				TSharedPtr<FWeapon> newWeapon;
				CreateWeapon(netItem.Index, newWeapon);
				Weapons.Emplace(MoveTemp(newWeapon));
				curWeapon = Weapons.Last();
			}
			else {
				curWeapon = Weapons[weaponIdx];
			}
			curWeapon->BindNetData(netItem);
		}			
		break;

		case EProductType::ARMOR:		[[fallthrough]];			
		case EProductType::HELMET:		[[fallthrough]];
		case EProductType::GLOVES:		[[fallthrough]];
		case EProductType::BOOTS:
		{
			TSharedPtr<FArmor> curArmor;
			int weaponIdx = Armors.IndexOfByPredicate([netItem](const TSharedPtr<FArmor>& row) {
				return row->id == netItem.ID;
				});
			if (weaponIdx == -1) {
				TSharedPtr<FArmor> newArmor;
				CreateArmor(netItem.Index, newArmor);
				Armors.Emplace(MoveTemp(newArmor));
				curArmor = Armors.Last();
			}
			else {
				curArmor = Armors[weaponIdx];
			}
			curArmor->BindNetData(netItem);
		}
		break;
		case EProductType::CONSUMABLE:	[[fallthrough]];
		case EProductType::QUESTITEM:	[[fallthrough]];
		case EProductType::NONE:		[[fallthrough]];
		default:
			break;
		}
	}
}
