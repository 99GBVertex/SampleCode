// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordManState_Idle.h"
#include "Character/AI/AISwordMan.h"

void USwordManState_Idle::StartState()
{
	// Init StateBase
	CharacterAnimState = ECharacterState::IDLE;
	if (!IsValid(SwordManCharacter)){
		//Error Log
		return;
	}
	
	TObjectPtr<UAISwordMan> curAnimInstance = SwordManCharacter->GetAI();
	if(!IsValid(curAnimInstance)) {
		// Error Log
		return;
	}
	curAnimInstance->SetCurrentCharState(CharacterAnimState);

	// Init StateIdle

}

void USwordManState_Idle::BindEventCalls()
{
	EVENT()->AddStateReceiver(this, { EEventType::msg_rpl_changeequip });
}

void USwordManState_Idle::OnBoundEventBroadCast(EEventType eventType, EventMsgPtr message)
{
	switch (eventType)
	{
	case EEventType::msg_rpl_changeequip:
	{
		if (IsValid(SwordManCharacter)) 
		{
			TObjectPtr<UAISwordMan> swordmanAI = SwordManCharacter->GetAI();
			if (IsValid(swordmanAI)) {
				swordmanAI->SG_Idle_ChangeWeapon();
			}
		}
	}
	break;

	default:
		break;
	}
}

void USwordManState_Idle::UnBindEventCalls()
{
	EVENT()->RemoveStateReceiver(this, { EEventType::msg_rpl_changeequip });
}

void USwordManState_Idle::EndState()
{
}