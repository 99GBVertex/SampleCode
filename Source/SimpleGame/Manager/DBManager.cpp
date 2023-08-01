// Fill out your copyright notice in the Description page of Project Settings.


#include "DBManager.h"
#include "Engine/DataTable.h"
#include "ItemManager.h"

void UDBManager::Init()
{
	LoadDBTables();
}

void UDBManager::Release()
{
	DataTables.Empty();
}

void UDBManager::LoadDBTables()
{
	TArray<FString> findFileNames;
	FindDBFiles(findFileNames);

	for (const FString& findFileName : findFileNames)
	{
		UDataTable* dbTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *findFileName));
		if (!DataTables.Contains(dbTable))
		{
			DataTables.Emplace(dbTable);
			UE_LOG(LogTemp, Display, TEXT("After Add DBTable : %s"), *findFileName);
		}
	}

	if (DataTables.Num() > 0)
	{
		// get tables
		UItemManager::Instance()->MakeItemDataTable();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DataTables is empty"));
	}
}

void UDBManager::FindDBFiles(TArray<FString>& FindFiles)
{
	TArray<FString> folders;
	folders.Emplace(TEXT("DB"));
	folders.Emplace(TEXT("DB/UI"));

	for (const FString& folder : folders)
	{
		TArray<FString> files;
		IFileManager::Get().FindFiles(files, *(FPaths::ProjectContentDir() + folder), TEXT(".uasset"));
		for (const FString& file : files)
		{
			FindFiles.Emplace(TEXT("/Game/") + folder + TEXT("/") + FPaths::GetBaseFilename(file));
		}
	}
}

const UDataTable* UDBManager::FindDataTable(const FString& TableName)
{
	for (const UDataTable* dataTable : DataTables)
	{
		dataTable->IsA<UDataTable>();
		if (TableName.Compare(dataTable->GetName()))
		{
			return dataTable;
		}
	}

	return nullptr;
}