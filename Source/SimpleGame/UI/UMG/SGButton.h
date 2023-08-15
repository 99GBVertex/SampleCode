// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "SGButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClickedReturnSelfEvent, UWidget*, ClickedWidget);

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API USGButton : public UButton
{
	GENERATED_UCLASS_BODY()

protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface

	//~ Begin UButton Interface
	FReply SlateHandleClicked();
	void SlateHandlePressed();
	void SlateHandleReleased();
#if WITH_EDITOR || PLATFORM_WINDOWS
	void SlateHandleHovered();
	void SlateHandleUnhovered();
#endif
	//~ End UButton Interface

public:
	/** Called after OnClicked */
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
		FOnButtonClickedReturnSelfEvent OnClickedReturnSelf;
	
};
