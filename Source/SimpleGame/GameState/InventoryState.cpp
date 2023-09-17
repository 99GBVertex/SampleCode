// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/InventoryState.h"
#include "Character/SwordManCharacter.h"
#include "Manager/NetworkManager.h"
#include "Manager/UIManager.h"

void UInventoryState::RegisterDelegates()
{
}

void UInventoryState::StartState()
{
	UNetworkManager::Instance()->SendGetInventory();
}

void UInventoryState::BindEventCalls()
{
	EVENT()->AddStateReceiver(this, { EEventType::msg_rpl_inventory });
}

void UInventoryState::OnBoundEventBroadCast(EEventType eventType, EventMsgPtr message)
{
	switch (eventType)
	{
	case EEventType::msg_rpl_inventory:
	{
		//Create UI
		UUIManager::Instance()->CreateUI(EUIObjectType::PAGE_INVENTORY);
	}
	break;

	default:
		break;
	}
}

void UInventoryState::UnBindEventCalls()
{
	EVENT()->AddStateReceiver(this, { EEventType::msg_rpl_inventory });
}

void UInventoryState::EndState()
{
}

void UInventoryState::UnregisterDelegates()
{
}
