// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Define.h"
#include "DB/ItemTable.h"
#include "Manager/NetworkManager.h"

#include "DesignPattern/Singleton.h"
#include "ItemManager.generated.h"

USTRUCT()
struct SIMPLEGAME_API FPhysXData
{
	GENERATED_BODY()

public:
	UPROPERTY()	int32 weight = 0;
	// etc..
};

USTRUCT()
struct SIMPLEGAME_API FResourceData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)	TSoftObjectPtr<UStaticMesh> mesh_Optr = nullptr;
	UPROPERTY(EditAnywhere) TSoftObjectPtr<UPaperSprite> sprite_Optr = nullptr;
};

USTRUCT()
struct SIMPLEGAME_API FProductData
{
	GENERATED_BODY()

public:
	UPROPERTY()	EProductSection productSection = EProductSection::NONE;
	UPROPERTY()	EProductType productType = EProductType::NONE;
};

USTRUCT()
struct SIMPLEGAME_API FAttributeInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()	EAttributeSection attributeSection = EAttributeSection::NONE;
	UPROPERTY()	EAttributeType attributeType = EAttributeType::NONE;
	UPROPERTY()	int32 attributeValue = 0;
};

USTRUCT()
struct SIMPLEGAME_API FItemBase
{
	GENERATED_BODY()

	virtual ~FItemBase() {
		nameTableKey.Empty();
		descriptTableKey.Empty();
		id = 0;
		index = 0;
	}

public:
	FItemBase() = default;
	FItemBase(const FItemBase&) = delete;
	FItemBase& operator=(const FItemBase&) = default;

public:
	UPROPERTY() int64 id = 0;
	UPROPERTY() int32 index = 0;
	UPROPERTY() int64 expireDate = 0;
	UPROPERTY()	FProductData productData;
private:
	TArray<TSharedPtr<FAttributeInfo>> attributeList;
	FString nameTableKey = "";
	FString descriptTableKey = "";

public:
	void SetTableKey();
	bool IsExpired() const;
	bool IsValid() const;
	FText GetName() const { return SIMPLE_LOCTEXT(nameTableKey); };
	FText GetDescription() const { return SIMPLE_LOCTEXT(descriptTableKey); };
	TArray<const FAttributeInfo*> GetAttributes() const;
};

USTRUCT()
struct SIMPLEGAME_API FWeapon : public FItemBase
{
	GENERATED_BODY()	
};

USTRUCT()
struct SIMPLEGAME_API FArmor : public FItemBase
{
	GENERATED_BODY()
};

USTRUCT()
struct SIMPLEGAME_API FEquipmentSlot
{
	GENERATED_BODY()
	
public:	
	TWeakPtr<FWeapon> mainWeapon;
	TWeakPtr<FWeapon> subWeapon;
	TWeakPtr<FArmor> helmet;
	TWeakPtr<FArmor> armer;
	TWeakPtr<FArmor> gloves;
	TWeakPtr<FArmor> boots;

	UPROPERTY() uint8 slotIndex = 0;
};

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
	FItemTable* GetItemData(int32 inIndex);

	// bind network
	void BindInventoryData(TArray<NetItemData*>& netItems, TArray<NetAttributeData*>& netAtts);

private:
	// table data
	TArray<FItemTable> ItemTable;

	// base structure
	TArray<TSharedPtr<FWeapon>> Weapons;
	TArray<TSharedPtr<FArmor>> Armors;
	TArray<TSharedPtr<FEquipmentSlot>> equipmentSlots;
};
