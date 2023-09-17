// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/GameEvent/EventManager.h"
#include "Manager/GameEvent/EventType.h"
#include "Misc/SimpleEngineUtil.h"
#include "UI/UMG/SimpleUserWidget.h"
#include "SimpleMsgUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API USimpleMsgUserWidget : public USimpleUserWidget
{
	GENERATED_BODY()

public:
	/**
	* Bind Event Calls
	*/
	virtual void BindEventCalls() {};

	/**
	* BroadCast Event
	*/
	virtual void OnBoundEventBroadCast(EEventType eventType, EventMsgPtr message) {};

	/**
	* UnBind Event Calls
	*/
	virtual void UnBindEventCalls() {};
	
};
