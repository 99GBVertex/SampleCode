// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceProvider.h"
#include "PaperSpriteAtlas.h"
#include "Engine/ObjectLibrary.h"

void UResourceProvider::Init()
{
	ObjectLibrary = UObjectLibrary::CreateLibrary(nullptr, false, false);
}

void UResourceProvider::Release()
{
	ObjectLibrary = nullptr;
}

const TSoftObjectPtr<UPaperSprite> UResourceProvider::GetTypeDefaultUI(EProductType pType)
{
	if (DefaultUIObjectTable.Num() && DefaultUIObjectTable.Contains(pType)) {
		return DefaultUIObjectTable[pType].LoadSynchronous();
	}
	if(!ObjectLibrary) {
		return nullptr;
	}
	TArray<FAssetData> assetList;
	ObjectLibrary->LoadAssetDataFromPath(UI_UMG_ATLAS_RESOURCE_PATH);	
	ObjectLibrary->GetAssetDataList(assetList);

	TMap<FName, EProductType> loadTarget = {
		{ "SP_WeaponDefault",	EProductType::WEAPON }, 
		{ "SP_ArmorDefault",	EProductType::ARMOR },
		{ "SP_HelmetDefault",	EProductType::HELMET },
		{ "SP_GlovesDefault",	EProductType::GLOVES },
		{ "SP_BootsDefault",	EProductType::BOOTS },
	};
	for(const FAssetData& asset : assetList) 
	{
		if(loadTarget.Contains(asset.AssetName))
		{
			EProductType pType = loadTarget[asset.AssetName];
			DefaultUIObjectTable.Emplace(pType, TSoftObjectPtr<UPaperSprite>(asset.GetSoftObjectPath()));
		}
	}
	if (DefaultUIObjectTable.Num() ==0 || !DefaultUIObjectTable.Contains(pType)) {
		return nullptr;
	}
	return DefaultUIObjectTable[pType].LoadSynchronous();
}
