// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestServerDefine.h"

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