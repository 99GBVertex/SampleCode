// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DesignPattern/Singleton.h"
#include "UIManager.generated.h"

class UUserWidget;
class UMasterWidget;
class USimpleUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIEvent, UUserWidget*, widget);

UENUM()
enum class EUIObjectType : uint8
{
	NONE,
	PAGE_INVENTORY,
};

UENUM()
enum class EUIType : uint8
{
	NONE,
	PAGE,
	POPUP,
	SYSTEM_POPUP,
};

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UUIManager : public UObject, public FSingleton<UUIManager>
{
	GENERATED_BODY()

	UUIManager();
public:
	void Init();
	void Release();

	void InitMaster();
	TObjectPtr<USimpleUserWidget> CreateUI(EUIObjectType InUIObjType);

protected:
	template<typename T>
	TObjectPtr<T> LoadWidget(const TObjectPtr<class UPanelWidget> RootUI, const FString& LoadPath) {
		TObjectPtr<T> UIWidget = nullptr;
		TSubclassOf<T> WidgetClass = LoadClass<T>(nullptr, *LoadPath);
		if (WidgetClass != nullptr)
		{
			UIWidget = CreateWidget<USimpleUserWidget>(RootUI, WidgetClass);
			UOverlaySlot* layerSlot = dynamic_cast<UOverlaySlot*>(RootUI->AddChild(UIWidget));
			if (layerSlot) {
				layerSlot->SetHorizontalAlignment(HAlign_Fill);
				layerSlot->SetVerticalAlignment(VAlign_Fill);
				layerSlot->SynchronizeProperties();
			}
		}
		return UIWidget;
	}

	static constexpr EUIType GetUIType(EUIObjectType InUIObjType);
	static constexpr const char* GetUIPath(EUIType InUIType);
	static constexpr const char* GetUIName(EUIObjectType InUIObjType);
protected:
	UPROPERTY() TSubclassOf<UUserWidget> MasterWidgetClass;
	UPROPERTY() TObjectPtr<UMasterWidget> MaterWidget;

	UPROPERTY() TObjectPtr<USimpleUserWidget> CurrentWidget;
	// Delete while waiting for the deletion animation
	UPROPERTY() TArray<TObjectPtr<USimpleUserWidget>> DestroyPool;

public:
	UPROPERTY(BlueprintAssignable)
		FUIEvent ConstructDelegate;
	UPROPERTY(BlueprintAssignable)
		FUIEvent DenstructDelegate;
};