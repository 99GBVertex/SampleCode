// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/UIManager.h"
#include "Define.h"
#include "SimpleGameInstnace.h"
#include "Misc/SimpleEngineUtil.h"
#include "UI/UMG/SimpleUserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/UMG/MasterWidget.h"
#include "Components/PanelWidget.h"
#include "Components/OverlaySlot.h"

UUIManager::UUIManager()
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/UMG/Common/W_Master"));
		if (WidgetClassFinder.Class != NULL) {
			MasterWidgetClass = WidgetClassFinder.Class;
		}
	}
}

void UUIManager::Init()
{
}

void UUIManager::Release()
{
	MaterWidget = nullptr;
	if (IsValid(CurrentWidget)) {
		CurrentWidget->UIDestructor();
	}
	CurrentWidget = nullptr;
	for (TObjectPtr<USimpleUserWidget>& widget : DestroyPool) {
		if (IsValid(widget)) {
			widget->UIDestructor();
		}
		widget = nullptr;
	}
	DestroyPool.Empty();
}

void UUIManager::InitMaster()
{
	TObjectPtr<USimpleGameInstnace> gInstance = SimpleEngineUtil::GetGameInstance<USimpleGameInstnace>();
	MaterWidget = CreateWidget<UMasterWidget>(gInstance, MasterWidgetClass);
	if (MaterWidget) {
		MaterWidget->AddToViewport();
	}
}

TObjectPtr<USimpleUserWidget> UUIManager::CreateUI(EUIObjectType InUIObjType)
{
	if (!MaterWidget) {
		InitMaster();
	}
	check(MaterWidget);

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
	EUIType uiType = UUIManager::GetUIType(InUIObjType);
	const TObjectPtr<UPanelWidget> rootLayer = MaterWidget->GetTypeRoot(uiType);
		
	FString StrResourceName = UUIManager::GetUIName(InUIObjType);
	FString StrResourcePath = FString::Format(TEXT("{0}{1}.{2}_C"), { UUIManager::GetUIPath(uiType), StrResourceName, StrResourceName });
 	CurrentWidget = LoadWidget<USimpleUserWidget>(rootLayer, StrResourcePath);
	if (CurrentWidget) {
		CurrentWidget->UIConstuctor();
	}
	return CurrentWidget;
}

constexpr EUIType UUIManager::GetUIType(EUIObjectType InUIObjType)
{
	EUIType OutUIType = EUIType::NONE;
	switch (InUIObjType)
	{
	case EUIObjectType::PAGE_INVENTORY:
		OutUIType = EUIType::PAGE;
		break;
	case EUIObjectType::NONE:
	default:
		break;
	}

	return OutUIType;
}

constexpr const char* UUIManager::GetUIPath(EUIType InUIType)
{
	switch (InUIType)
	{
	case EUIType::PAGE:		   	return UI_PAGE_RESOURCE_PATH;		
	case EUIType::POPUP:	   	return UI_POPUP_RESOURCE_PATH;		
	case EUIType::SYSTEM_POPUP:	return UI_SYSTEM_POPUP_RESOURCE_PATH;
	case EUIType::NONE:
	default:
		break;
	}
	return "";
}

constexpr const char* UUIManager::GetUIName(EUIObjectType InUIObjType)
{
	EUIType UIType = GetUIType(InUIObjType);
	switch (InUIObjType)
	{
	case EUIObjectType::PAGE_INVENTORY:	return "W_InventoryPage";
	case EUIObjectType::NONE:
	default:
		break;
	}
	return "";
}
