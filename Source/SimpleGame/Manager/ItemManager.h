// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Define.h"
#include "DB/ItemTable.h"
#include "ItemStruct.h"

#include "DesignPattern/Singleton.h"
#include "ItemManager.generated.h"

struct FNetItemData;
struct FNetAttributeData;

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UItemManager : public UObject, public FSingleton<UItemManager>
{
	GENERATED_BODY()

public:
	void Init();
	void Release();

	// table data
	void MakeItemDataTable();
	const FItemTable* GetItemData(int32 inIndex);

	// bind network
	bool CreateWeapon(int32 inIndex, TSharedPtr<FWeapon>& outWeapon);
	bool CreateArmor(int32 inIndex, TSharedPtr<FArmor>& outArmor);
	void BindInventoryData(const TArray<FNetItemData>& netItems, const TArray<FNetAttributeData>& netAtts);

	// Optimization// Data collect steps before post to server by Frequent Request
	void UpdateItemPrepare(int64 id, uint8 slotIdx, EProductType pType, EEquipState eState);
	void UpdateItemImmediately(int64 id, uint8 slotIdx, EProductType pType, EEquipState eState);
	void UpdateItemsToServer();

	// Getter
	TWeakPtr<FEquipmentSlot> GetEquipment(uint8 slotIdx);
	TArray<TWeakPtr<FWeapon>> GetWeapons(EProductSection typeSection = EProductSection::NONE);
	TArray<TWeakPtr<FArmor>> GetArmors(EProductSection typeSection = EProductSection::NONE);

private:
	// table data
	TArray<FItemTable> ItemTable;

	// base structure	
	TArray<TSharedPtr<FWeapon>> Weapons;
	TArray<TSharedPtr<FArmor>> Armors;

	TArray<TSharedPtr<FEquipmentSlot>> EquipmentSlots;
};
