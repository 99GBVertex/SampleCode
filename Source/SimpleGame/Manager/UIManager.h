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

	EUIType GetUIType(const FString& name);

	template<typename T>
	TObjectPtr<T> LoadWidget(const TObjectPtr<class UWidget> RootUI, const FString& LoadPath) {
		TObjectPtr<T> UIWidget = nullptr;
		TSubclassOf<T> WidgetClass = LoadClass<T>(nullptr, *LoadPath);
		if (WidgetClass != nullptr)
		{
			UIWidget = CreateWidget<T>(RootUI, WidgetClass);
		}
		return UIWidget;
	}

	TObjectPtr<USimpleUserWidget> CreateUI(const FString& name);

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