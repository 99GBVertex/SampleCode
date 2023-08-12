// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/StringFwd.h"
#include "DesignPattern/Singleton.h"
#include "DBManager.generated.h"

class UDataTable;
/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UDBManager : public UObject, public FSingleton<UDBManager>
{
	GENERATED_BODY()

public:
	void Init();
	void Release();

	void LoadDBTables();
	void FindDBFiles(TArray<FString>& FindFiles);

	template <class TableType>
	void GetDataTableRows(const FString& TableName, TArray<TableType*>& RowArray);

	template <class TableType>
	void GetAllDataTableRows(const FString& TableName, TArray<FName>& KeyArray, TArray<TableType*>& RowArray);

private:
	const UDataTable* FindDataTable(const FString& TableName);

	UPROPERTY() TArray<UDataTable*> DataTables;
};

template <class TableType>
void UDBManager::GetDataTableRows(const FString& TableName, TArray<TableType*>& RowArray)
{
	const UDataTable* DataTable = FindDataTable(TableName);
	check(DataTable);

	DataTable->GetAllRows<TableType>(TEXT(""), RowArray);
}

template <class TableType>
void UDBManager::GetAllDataTableRows(const FString& TableName, TArray<FName>& KeyArray, TArray<TableType*>& RowArray)
{
	const UDataTable* DataTable = FindDataTable(TableName);
	check(DataTable);

	KeyArray = DataTable->GetRowNames();
	DataTable->GetAllRows<TableType>(TEXT(""), RowArray);
}
