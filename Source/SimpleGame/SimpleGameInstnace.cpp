// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleGameInstnace.h"
#include "Manager/DBManager.h"
#include "Manager/ItemManager.h"

USimpleGameInstnace::USimpleGameInstnace()
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{		
	}
}

USimpleGameInstnace::~USimpleGameInstnace()
{
}



void USimpleGameInstnace::Init()
{
	Super::Init();

	UDBManager::Instance();
	UItemManager::Instance();

	UDBManager::Instance()->Init();
}

void USimpleGameInstnace::Shutdown()
{
	Super::Shutdown();
}

void USimpleGameInstnace::StartGameInstance()
{
	Super::StartGameInstance();
}
