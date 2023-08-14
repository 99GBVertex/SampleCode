// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SimpleGameInstnace.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API USimpleGameInstnace : public UGameInstance
{
	GENERATED_BODY()
public:
	USimpleGameInstnace();
	virtual ~USimpleGameInstnace();

	//~ Begin UGameInstance
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;
	//~ End UGameInstance

private:
	TObjectPtr<class UEventManager> eventMgr;
	TObjectPtr<class UResourceProvider> resourceProvier;

	friend class SimpleEngineUtil;
};
