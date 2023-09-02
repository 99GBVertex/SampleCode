// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/SimpleEngineUtil.h"
#include "SimpleGameInstnace.h"

TObjectPtr<UWorld> SimpleEngineUtil::ModeWorld = nullptr;
FName SimpleEngineUtil::LandscapeProfileName = "LandscapeProfile";

TObjectPtr<UWorld> GetModeWorld()
{
	return SimpleEngineUtil::ModeWorld;
}

SimpleEngineUtil::SimpleEngineUtil()
{
}

SimpleEngineUtil::~SimpleEngineUtil()
{
}

UEventManager* SimpleEngineUtil::GetPublicEventManager()
{
	TObjectPtr<USimpleGameInstnace> SGInstance = SimpleEngineUtil::GetGameInstance<USimpleGameInstnace>();
	if (IsValid(SGInstance) && SGInstance->IsValidLowLevel()) {
		return SGInstance->eventMgr;
	}
	return nullptr;
}

UResourceProvider* SimpleEngineUtil::GetPublicResourceProvider()
{
	TObjectPtr<USimpleGameInstnace> SGInstance = SimpleEngineUtil::GetGameInstance<USimpleGameInstnace>();
	if (IsValid(SGInstance) && SGInstance->IsValidLowLevel()) {
		return SGInstance->resourceProvier;
	}
	return nullptr;
}
