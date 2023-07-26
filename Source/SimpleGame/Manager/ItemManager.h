// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../DesignPattern/Singleton.h"
#include "ItemManager.generated.h"

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

	void MakeItemDataTable();
	
};
