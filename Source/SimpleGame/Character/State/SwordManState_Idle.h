// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/State/SwordManState_Base.h"
#include "SwordManState_Idle.generated.h"


UCLASS()
class SIMPLEGAME_API USwordManState_Idle : public USwordManState_Base
{
	GENERATED_BODY()

public:
	//~ Begin UState
	virtual void StartState() override;

	virtual void BindEventCalls() override;
	virtual void OnBoundEventBroadCast(EEventType eventType, EventMsgPtr message) override;
	virtual void UnBindEventCalls() override;

	virtual void EndState() override;
	//~ End UState
};
