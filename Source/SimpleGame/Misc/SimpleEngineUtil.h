// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

/**
 *
 */
class SimpleEngineUtil
{
public:
	SimpleEngineUtil();
	~SimpleEngineUtil();

	/**
	* GameInstance ����
	* @return   GameInstance
	*/
	template <typename InstanceType>
	static TObjectPtr<InstanceType> GetGameInstance()
	{
		UWorld* World = ModeWorld;
		if (World == nullptr || !World->IsValidLowLevel())
			return nullptr;

		return Cast<InstanceType>(World->GetGameInstance());
	}

	template<typename TimerHandleType>
	static void ClearTimer(TimerHandleType& Handle)
	{
		UWorld* World = ModeWorld;
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
	* GameMode ����
	* @return   GameMode
	*/
	template <typename ModeType>
	static ModeType* GetGameMode()
	{
		UWorld* World = ModeWorld;
		if (World == nullptr)
			return nullptr;

		AGameModeBase* GameModeBase = World->GetAuthGameMode();
		if (GameModeBase == nullptr)
		{
			return nullptr;
		}

		ModeType* ret = Cast<ModeType>(World->GetAuthGameMode());

		return ret;
	}

	/**
	* ���忡�� ���͸� ã�´�.
	* @param	World	����
	* @param	Name	���� �̸�
	* @return   ã�� ����
	*/
	template <typename ActorType>
	static ActorType* FindActor(UWorld* World, const FString& Name)
	{
		check(World);

		for (TActorIterator<ActorType> ActorItr(World); ActorItr; ++ActorItr)
		{
			ActorType* Actor = *ActorItr;
			if (UKismetSystemLibrary::GetDisplayName(Actor) == Name)
			{
				return Actor;
			}
		}

		return nullptr;
	}

	/**
	* ������Ʈ�� ã�´�.
	* @param	Name	������Ʈ �̸�.
	* @return   ã�� ������Ʈ
	*/
	template <typename ObjectType>
	static ObjectType* FindObject(const FString& Name)
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


	/** ���彺������ �������� �̸� */
	static FName LandscapeProfileName;

	/** ��� GetWorld. �Ʒ��� GetModeWorld() �� ���� */
	static UWorld* ModeWorld;
};

/**
* ��� GetWorld
*/
extern UWorld* GetModeWorld();