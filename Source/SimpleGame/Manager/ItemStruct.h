// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Define.h"
#include "PaperSpriteAtlas.h"
#include "ItemStruct.generated.h"

class NetItemData;

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
	UPROPERTY()	EProductGrade productGrade = EProductGrade::NONE;
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
	FItemBase(const FItemBase & aa) = delete;

public:
	UPROPERTY() int64 id = 0;
	UPROPERTY() int32 index = 0;
	UPROPERTY() int64 expireDate = 0;
	UPROPERTY() EEquipState equipState = EEquipState::NONE;
	UPROPERTY()	FProductData productData;
	UPROPERTY()	FResourceData resourceData;
private:
	TArray<TSharedPtr<FAttributeInfo>> attributeList;
	FString nameTableKey = "";
	FString descriptTableKey = "";

public:
	void BindNetData(const NetItemData& InNetData);
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