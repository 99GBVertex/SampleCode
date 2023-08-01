// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleGameInstnace.h"
#include "Manager/DBManager.h"
#include "Manager/ItemManager.h"
#include "Manager/NetworkManager.h"

USimpleGameInstnace::USimpleGameInstnace()
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		UDBManager::Instance();
		UItemManager::Instance();
		UNetworkManager::Instance();
	}
}

USimpleGameInstnace::~USimpleGameInstnace()
{
}

void USimpleGameInstnace::Init()
{
	Super::Init();

	UDBManager::Instance()->Init();
	UItemManager::Instance()->Init();
	UNetworkManager::Instance()->Init();
}

void USimpleGameInstnace::Shutdown()
{
	UDBManager::Instance()->Release();
	UItemManager::Instance()->Release();
	UNetworkManager::Instance()->Release();

	Super::Shutdown();
}

void USimpleGameInstnace::StartGameInstance()
{
	Super::StartGameInstance();
}
