// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/InventoryState.h"
#include "Manager/UIManager.h"

void UInventoryState::RegisterDelegates()
{
}

void UInventoryState::StartState()
{
	UUIManager::Instance()->CreateUI(EUIObjectType::PAGE_INVENTORY);
}

void UInventoryState::EndState()
{
}

void UInventoryState::UnregisterDelegates()
{
}
