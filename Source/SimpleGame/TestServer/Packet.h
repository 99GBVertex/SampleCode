// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestServerDefine.h"
#include "Packet.generated.h"

/**
 * Is not a general structure
 * like TestClinet, Database is ClientOnly
 */

 /*
 * as UObject for convenience or UStruct
 */
 UCLASS()
class USimplePacket : public UObject
{
	 GENERATED_BODY()
public:

	ProtocolId protocolId = ProtocolId::None;
};

USTRUCT()
struct FNetItemData
{
	GENERATED_BODY()
public:
	int64 ID			= 0;
	int64 ExpireDate	= 0;
	int32 Index			= 0;
	int32 Quantity		= 0;
	uint8 Level			= 0;
	uint8 EquipState	= 0;
};

USTRUCT()
struct FNetAttributeData
{
	GENERATED_BODY()
public:
	int64 ParentsID			= 0;
	int64 AttributeID		= 0;
	uint8 AttributeType		= 0;
	uint8 AttributeValue	= 0;
};

UCLASS()
class UQrySimpleHello : public USimplePacket
{
	GENERATED_BODY()
public:
	int32 accountID;
};

UCLASS()
class URplSimpleHello : public USimplePacket
{
	GENERATED_BODY()
public:
	NetResultCode resultCode = NetResultCode::NoError;
	int64 accountTocken;
};

UCLASS()
class UQrySimpleGetInventory : public USimplePacket
{
	GENERATED_BODY()
};

UCLASS()
class URplSimpleGetInventory : public USimplePacket
{
	GENERATED_BODY()
public:
	NetResultCode resultCode = NetResultCode::NoError;
	TArray<FNetItemData> NetItemDatas;
	TArray<FNetAttributeData> NetAttDatas;
};