// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/StartState.h"
#include "DesignPattern/StateType.h"
#include "Manager/NetworkManager.h"
#include "Manager/UIManager.h"
#include "SimpleGameMode.h"

void UStartState::RegisterDelegates()
{
}

void UStartState::StartState()
{
	UNetworkManager::Instance()->SendHello();
}

void UStartState::BindEventCalls()
{
	if(EVENT_MANAGER()) EVENT_MANAGER()->AddReceiver(this, { EEventType::msg_rpl_hello });
}

void UStartState::OnBoundEventBroadCast(EEventType eventType, EventMsgPtr message)
{
	switch (eventType)
	{
	case EEventType::msg_rpl_hello:
	{
		TObjectPtr<ASimpleGameMode> curGameMode = SimpleEngineUtil::GetGameMode<ASimpleGameMode>();
		if (IsValid(curGameMode) && curGameMode->IsValidLowLevel()) {			
			curGameMode->ChangeStateEnum(EGameState::INVENTORY);
		}
	}
	break;

	default:
		break;
	}
}

void UStartState::UnBindEventCalls()
{
	if (EVENT_MANAGER()) EVENT_MANAGER()->AddReceiver(this, { EEventType::msg_rpl_hello });
}

void UStartState::EndState()
{
}

void UStartState::UnregisterDelegates()
{
}
