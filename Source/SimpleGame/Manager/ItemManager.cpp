// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"
#include "../DB/ItemTable.h"
#include "../Manager/DBManager.h"

void UItemManager::Init()
{
}

void UItemManager::Release()
{
}

void UItemManager::MakeItemDataTable()
{
	TArray<FItemTable*> tempItemTable;
	UDBManager::Instance()->GetDataTableRows<FItemTable>(TEXT("ItemTable"), tempItemTable);
}
