// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

#define EVENT SimpleEngineUtil::GetPublicEventManager
#define RESOURCE SimpleEngineUtil::GetPublicResourceProvider
/**
 *
 */
class SimpleEngineUtil
{
public:
	SimpleEngineUtil();
	~SimpleEngineUtil();

	/**
	* GameInstance 리턴
	* @return   GameInstance
	*/
	template <typename InstanceType>
	static TObjectPtr<InstanceType> GetGameInstance()
	{
		TObjectPtr<UWorld> World = ModeWorld;
		if (World == nullptr || !World->IsValidLowLevel())
			return nullptr;

		return Cast<InstanceType>(World->GetGameInstance());
	}

	template<typename TimerHandleType>
	static void ClearTimer(TimerHandleType& Handle)
	{
		TObjectPtr<UWorld> World = ModeWorld;
		if (World == nullptr)
		{
			return;
		}
		if (Handle.IsValid())
		{
			World->GetTimerManager().ClearTimer(Handle);
		}
	}

	/**
	* GameMode 리턴
	* @return   GameMode
	*/
	template <typename ModeType>
	static TObjectPtr<ModeType> GetGameMode()
	{
		TObjectPtr<UWorld> World = ModeWorld;
		if (World == nullptr)
			return nullptr;

		TObjectPtr<AGameModeBase> GameModeBase = World->GetAuthGameMode();
		if (GameModeBase == nullptr)
		{
			return nullptr;
		}

		TObjectPtr<ModeType> ret = Cast<ModeType>(World->GetAuthGameMode());

		return ret;
	}

	/**
	* 월드에서 액터를 찾는다.
	* @param	World	월드
	* @param	Name	액터 이름
	* @return   찾은 액터
	*/
	template <typename ActorType>
	static TObjectPtr<ActorType> FindActor(UWorld* World, const FString& Name)
	{
		check(World);

		for (TActorIterator<ActorType> ActorItr(World); ActorItr; ++ActorItr)
		{
			TObjectPtr<ActorType> Actor = *ActorItr;
			if (UKismetSystemLibrary::GetDisplayName(Actor) == Name)
			{
				return Actor;
			}
		}

		return nullptr;
	}

	/**
	* 오브젝트를 찾는다.
	* @param	Name	오브젝트 이름.
	* @return   찾은 오브젝트
	*/
	template <typename ObjectType>
	static TObjectPtr<ObjectType> FindObject(const FString& Name)
	{
		for (TObjectIterator<ObjectType> Itr; Itr; ++Itr)
		{
			if (Itr->GetName() == Name)
			{
				return *Itr;
			}
		}

		return nullptr;
	}


	/** 랜드스케이프 프로파일 이름 */
	static FName LandscapeProfileName;

	/** 모드 GetWorld. 아래의 GetModeWorld() 를 쓰자 */
	static TObjectPtr<UWorld> ModeWorld;

	static class UEventManager* GetPublicEventManager();
	static class UResourceProvider* GetPublicResourceProvider();
};

/**
* 모드 GetWorld
*/
extern TObjectPtr<UWorld> GetModeWorld();