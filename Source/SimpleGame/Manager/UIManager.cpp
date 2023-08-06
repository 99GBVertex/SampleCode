// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/UIManager.h"
#include "Define.h"
#include "UI/UMG/SimpleUserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/UMG/MasterWidget.h"

UUIManager::UUIManager()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/UMG/Common/W_Master"));
	if (WidgetClassFinder.Class != NULL) {
		MasterWidgetClass = WidgetClassFinder.Class;
	}
}

void UUIManager::Init()
{
	MaterWidget = CreateWidget<UMasterWidget>(GetWorld(), MasterWidgetClass);
	if (MaterWidget) {
		MaterWidget->AddToViewport();
	}
}

void UUIManager::Release()
{
	MasterWidgetClass = nullptr;
	MaterWidget = nullptr;
	CurrentWidget->UIDestructor();
	CurrentWidget = nullptr;
	for (TObjectPtr<USimpleUserWidget>& widget : DestroyPool) {
		widget->UIDestructor();
		widget = nullptr;
	}
	DestroyPool.Empty();
}

EUIType UUIManager::GetUIType(const FString& name)
{
	if (name.Contains("page"))
	{
		return EUIType::PAGE;
	}
	else if (name.Contains("system_popup"))
	{
		return EUIType::SYSTEM_POPUP;
	}
	else if (name.Contains("popup"))
	{
		return EUIType::POPUP;
	}
	return EUIType::NONE;
}

TObjectPtr<USimpleUserWidget> UUIManager::CreateUI(const FString& name)
{
	if (!MaterWidget) {
		return nullptr;
	}

	FString StrResourcePath = "";
	EUIType UIType = GetUIType(name);
	switch (UIType)
	{
	case EUIType::PAGE:		   	StrResourcePath = UI_PAGE_RESOURCE_PATH;			break;
	case EUIType::POPUP:	   	StrResourcePath = UI_POPUP_RESOURCE_PATH;			break;
	case EUIType::SYSTEM_POPUP:	StrResourcePath = UI_SYSTEM_POPUP_RESOURCE_PATH;	break;
	case EUIType::NONE:
	default:
		break;
	}

	if (IsValid(CurrentWidget)) {
		if (CurrentWidget->IsDestroyImmediately()) {
			CurrentWidget->UIDestructor();
			CurrentWidget = nullptr;
		}
		else {
			DestroyPool.Emplace(MoveTemp(CurrentWidget));
			CurrentWidget = nullptr;
		}
	}
	const TObjectPtr<UWidget> rootLayer = MaterWidget->GetTypeRoot(UIType);
	CurrentWidget = LoadWidget<USimpleUserWidget>(rootLayer, StrResourcePath);
	if (CurrentWidget) {
		CurrentWidget->UIConstuctor();
	}

	return CurrentWidget;
}