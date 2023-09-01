// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"
#include "PaperSpriteAtlas.h"
#include "Manager/DBManager.h"
#include "Manager/NetworkManager.h"

void UItemManager::Init()
{
	Weapons.Empty();
	Armors.Empty();
	EquipmentSlots.Empty();

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
		copyRow.item_mesh_ik_offset = row->item_mesh_ik_offset;
		copyRow.item_effect_Optr	= row->item_effect_Optr;
		ItemTable.Emplace(MoveTemp(copyRow));
	}
}

const TObjectPtr<FItemTable> UItemManager::GetItemData(int32 inIndex)
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
	outWeapon->productData.productGrade = curItem->itemGrade;

	outWeapon->resourceData.sprite_Optr = curItem->item_sprite_Optr;
	outWeapon->resourceData.mesh_Optr = curItem->item_mesh_Optr;
	outWeapon->resourceData.mesh_ik_offset = curItem->item_mesh_ik_offset;
	outWeapon->resourceData.item_effect_Optr = curItem->item_effect_Optr;

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

void UItemManager::BindInventoryData(const TArray<FNetItemData>& netItems, const TArray<FNetAttributeData>& netAtts)
{
	for (const FNetItemData& netItem : netItems) {
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

	InitEquipment();
}

void UItemManager::InitEquipment()
{
	// TODO : Add slot-specific interrupters when slot systems are added
	bool bEquipConflictFlag = false;

	TSharedPtr<FEquipmentSlot> equipment = nullptr;
	if (EquipmentSlots.Num() == 0) {
		equipment = MakeShared<FEquipmentSlot>();
		equipment->slotIndex = kDefaultSlotIdx;
		EquipmentSlots.Emplace(equipment);
	}
	equipment = EquipmentSlots[0];
	equipment->ClearEquipment();

	for (const TSharedPtr<FWeapon>& weapon : Weapons) 
	{
		if (weapon->equipState == EEquipState::EQUIP) 
		{
			if (equipment->mainWeapon.IsValid()) {
				bEquipConflictFlag = true;
				break;
			}
			equipment->mainWeapon = weapon;			
		}
	}
	
	for (const TSharedPtr<FArmor>& armor : Armors)
	{
		if (armor->equipState == EEquipState::EQUIP)
		{
			if (equipment->mainWeapon.IsValid()) {
				bEquipConflictFlag = true;
				break;
			}

			TWeakPtr<FArmor>* typeEquipment = nullptr;
			EProductType armorType = armor->productData.productType;
			switch (armorType)
			{
			case EProductType::ARMOR:	typeEquipment = &equipment->armor; break;
			case EProductType::HELMET:	typeEquipment = &equipment->helmet; break;
			case EProductType::GLOVES:	typeEquipment = &equipment->gloves; break;
			case EProductType::BOOTS:	typeEquipment = &equipment->boots; break;
			default:
				//log warning
				continue;
			}

			if (typeEquipment) {
				if ((*typeEquipment).IsValid()) {
					bEquipConflictFlag = true;
					break;
				}
				(*typeEquipment) = armor;
			}
		}
	}
	if (bEquipConflictFlag) {
		// todo go Interrupt flow
		return;
	}
}

bool UItemManager::UpdateItemPrepare(int64 id, uint8 slotIdx, EProductType pType, EEquipState eState)
{
	// pending data
	return false;
}

bool UItemManager::UpdateItemImmediately(const TWeakPtr<const FItemBase>& updateTarget, EEquipState eState)
{
	if (!updateTarget.IsValid() || !updateTarget.Pin()->IsValid()) {
		// log some reason
		return false;
	}
	const FItemBase* curTarget = updateTarget.Pin().Get();
	if (curTarget->IsExpired()) {
		// log some reason
		// remove item and reset
		return true;
	}

	const int64 tarID = curTarget->id;
	const EProductType tarPType = curTarget->productData.productType;

	const TWeakPtr<const FEquipmentSlot> curEquipmentSlot = GetEquipment(kDefaultSlotIdx);
	if (!curEquipmentSlot.IsValid()) {
		//log
		return false;
	}
	const TWeakPtr<const FItemBase> equippedItemMatches = curEquipmentSlot.Pin()->GetEquipment(tarPType);

	bool bRequiresEquipmentDetachFirst = false;
	bool bAlterable = false;

	if (eState == EEquipState::EQUIP) 
	{
		if (equippedItemMatches.IsValid())
		{
			if (equippedItemMatches.Pin()->id == tarID) {
				// log alreay equipped
				return false;
			}
			else {
				bRequiresEquipmentDetachFirst = true;
				bAlterable = true;
			}
		}
		else {
			bAlterable = true;
		}
	}
	else if (eState == EEquipState::UNEQUIP) 
	{
		if (equippedItemMatches.IsValid()) {
			bAlterable = true;
		}
		else {
			// log alreay unequipped
			return false;
		}
	}

	if (bRequiresEquipmentDetachFirst) {
		const FItemBase* curEquippedItem = equippedItemMatches.Pin().Get();
		FItemBase* modifiableEquippedItem = const_cast<FItemBase*>(curEquippedItem);
		if (modifiableEquippedItem) modifiableEquippedItem->equipState = EEquipState::UNEQUIP;
	}
	if (bAlterable) {
		FItemBase* modifiableTarget = const_cast<FItemBase*>(curTarget);
		if (modifiableTarget) modifiableTarget->equipState = eState;
	}

	InitEquipment();
	UpdateItemsToServer();
	return true;
}

bool UItemManager::UpdateItemsToServer()
{
	// pending data to Server
	return false;
}

TWeakPtr<const FEquipmentSlot> UItemManager::GetEquipment(uint8 slotIdx)
{
	TArray<TWeakPtr<const FEquipmentSlot>> outResult;
	outResult.Append(EquipmentSlots.FilterByPredicate([slotIdx](const TWeakPtr<const FEquipmentSlot>& row){
		if (!row.Pin()) return false;
		return row.Pin()->slotIndex == slotIdx;
	}));
	check(outResult.Num() == 1)
	return outResult[0];
}

TArray<TWeakPtr<const FWeapon>> UItemManager::GetWeapons(EProductSection typeSection)
{
	TArray<TWeakPtr<const FWeapon>> outResult;
	if (typeSection == EProductSection::NONE) {
		outResult.Append(Weapons);
	}
	else {
		outResult.Append(Weapons.FilterByPredicate([typeSection](const TWeakPtr<const FWeapon>& row) {
			if(!row.Pin()) return false;
			return row.Pin()->productData.productSection == typeSection;
		}));
	}
	return outResult;
}

TArray<TWeakPtr<const FArmor>> UItemManager::GetArmors(EProductSection typeSection)
{
	TArray<TWeakPtr<const FArmor>> outResult;
	if (typeSection == EProductSection::NONE) {
		outResult.Append(Armors);
	}
	else {
		outResult.Append(Armors.FilterByPredicate([typeSection](const TWeakPtr<const FArmor>& row) {
			if (!row.Pin()) return false;
			return row.Pin()->productData.productSection == typeSection;
		}));
	}
	return outResult;
}
