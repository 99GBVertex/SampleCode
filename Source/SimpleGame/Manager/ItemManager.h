// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Define.h"
#include "DB/ItemTable.h"
#include "ItemStruct.h"

#include "DesignPattern/Singleton.h"
#include "ItemManager.generated.h"

class NetItemData;
class NetAttributeData;

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
	void BindInventoryData(const TArray<NetItemData>& netItems, const TArray<NetAttributeData>& netAtts);

	// Getter
	TArray<TWeakPtr<FWeapon>> GetWeapons(EProductSection typeSection = EProductSection::NONE);

private:
	// table data
	TArray<FItemTable> ItemTable;

	// base structure	
	TArray<TSharedPtr<FWeapon>> Weapons;
	TArray<TSharedPtr<FArmor>> Armors;

	TArray<TSharedPtr<FEquipmentSlot>> EquipmentSlots;
};
