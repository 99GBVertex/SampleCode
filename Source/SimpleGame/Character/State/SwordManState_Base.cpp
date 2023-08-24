// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordManState_Base.h"

USwordManState_Base::USwordManState_Base()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && !IsValid(SwordManCharacter))
	{
		SwordManCharacter = Cast<ASwordManCharacter>(GetOuter());
		if (IsValid(SwordManCharacter))
		{
			//log
			return;
		}
		CharacterAnimState = ECharacterState::NONE;
	}
}