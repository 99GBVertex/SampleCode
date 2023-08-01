// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/ThreadSafeCounter.h"
#include "Tickable.h"
#include "TestServerDefine.h"
#include "Containers/Queue.h"
#include "TestServer.generated.h"

/**
 * Is not a general structure
 * like TestClinet, Database is ClientOnly
 */

class SimplePacket
{
public:
	SimplePacket() {};
	virtual ~SimplePacket() {};

	ProtocolId protocolId = ProtocolId::None;
};

class NetItemData
{
public:
	int64 ID			= 0;
	int64 ExpireDate	= 0;
	int32 Index			= 0;
	int32 Quantity		= 0;
	uint8 Level			= 0;
	uint8 EquipState	= 0;
};

class NetAttributeData
{
public:
	int64 ParentsID			= 0;
	int64 AttributeID		= 0;
	uint8 AttributeType		= 0;
	uint8 AttributeValue	= 0;
};

class QrySimpleHello : public SimplePacket
{
public:
	int32 accountID;
};

class RplSimpleHello : public SimplePacket
{
public:
	NetResultCode resultCode = NetResultCode::NoError;
	int64 accountTocken;
};

class QrySimpleGetInventory : public SimplePacket
{
};

class RplSimpleGetInventory : public SimplePacket
{
public:
	NetResultCode resultCode = NetResultCode::NoError;
	TArray<NetItemData> NetItemDatas;
	TArray<NetAttributeData> NetAttDatas;
};

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
