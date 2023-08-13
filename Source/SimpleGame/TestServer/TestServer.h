// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Packet.h"
#include "HAL/ThreadSafeCounter.h"
#include "Tickable.h"
#include "TestServerDefine.h"
#include "Containers/Queue.h"
#include "TestServer.generated.h"

/**
 * Is not a general structure
 * like TestClinet, Database is ClientOnly
 */

static constexpr int32 kItemDefaultPoolSize = 100;
static constexpr int32 kAttributeDefaultPoolSize = 200;

UCLASS()
class SIMPLEGAME_API UTestServer : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:

	void ServerOpen();
	void ServerClose();

	void AddBuffer(const SimplePacket* packet);

	// FTickableGameObject interface
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

	bool bAllowedToTick = false;
	virtual bool IsAllowedToTick() const override { return bAllowedToTick; }
	// End of FTickableGameObject interface

private:
	void Dispatch(const SimplePacket* qryPacket);

	// Game User Fuctions
	bool FillUserInventory(TArray<NetItemData>& refItemDatas, TArray<NetAttributeData>& refAttDatas);

private:
	TQueue<const SimplePacket*> packets;

	// not have structure by user
	TArray<NetItemData> ItemDatas;
	TArray<NetAttributeData> AttDatas;
};
