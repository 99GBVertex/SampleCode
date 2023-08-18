// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Define.h"
#include "ResourceProvider.generated.h"

class UPaperSprite;
class UObjectLibrary;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UResourceProvider : public UObject
{
	GENERATED_BODY()

public:
	void Init();
	void Release();
	const TSoftObjectPtr<UPaperSprite> GetTypeDefaultUI(EProductType pType);

private:
	TMap<EProductType, TSoftObjectPtr<UPaperSprite>> DefaultUIObjectTable = {};
	UPROPERTY() TObjectPtr<UObjectLibrary> ObjectLibrary = nullptr;
};

