// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimpleUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API USimpleUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void UIConstuctor();
	virtual void UIDestructor();

	virtual bool IsDestroyImmediately();	
};
