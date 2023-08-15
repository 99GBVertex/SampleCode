// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/SGButton.h"
#include "Components/ButtonSlot.h"

USGButton::USGButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

TSharedRef<SWidget> USGButton::RebuildWidget()
{
	MyButton = SNew(SButton)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandlePressed))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleased))
#if WITH_EDITOR || PLATFORM_WINDOWS
		.OnHovered_UObject(this, &ThisClass::SlateHandleHovered)
		.OnUnhovered_UObject(this, &ThisClass::SlateHandleUnhovered)
#endif
		.ButtonStyle(&WidgetStyle)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.IsFocusable(IsFocusable)
		;

	if (GetChildrenCount() > 0)
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
	}

	return MyButton.ToSharedRef();
}

FReply USGButton::SlateHandleClicked()
{
	OnClicked.Broadcast();
	OnClickedReturnSelf.Broadcast(this);

	return FReply::Handled();
}

void USGButton::SlateHandlePressed()
{
	OnPressed.Broadcast();
}

void USGButton::SlateHandleReleased()
{
	OnReleased.Broadcast();
}

void USGButton::SlateHandleHovered()
{
	OnHovered.Broadcast();
}

void USGButton::SlateHandleUnhovered()
{
	OnUnhovered.Broadcast();
}
