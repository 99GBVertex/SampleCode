// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/ThreadSafeCounter.h"
#include "TestServer.generated.h"

/**
 * Is not a general structure
 * like TestClinet, Database is ClientOnly
 */
class ISerializable
{
	virtual unsigned short Serialize(char* buffer, int32 offset) = 0;
};

class IDeserializable
{
	virtual unsigned short Deserialize(char* buffer, int32 offset) = 0;
};

class IPacketStructInit
{
	virtual void Init() = 0;
};

class RefObject
{
public:
	RefObject()
	{
		counter.Reset();
		counter.Increment();
	}
	virtual ~RefObject()
	{
	}
	void AddRef()
	{
		counter.Increment();
	}
	void RemoveRef()
	{
		counter.Decrement();
		if (0 >= counter.GetValue())
		{
			Destroy();
			delete this;
		}
	}
	int32 GetValue()
	{
		return counter.GetValue();
	}
protected:
	virtual void Destroy()
	{
	}
private:
	FThreadSafeCounter counter;
};

class IPacketStruct : public IPacketStructInit, public ISerializable, public IDeserializable, public RefObject
{
public:
	virtual uint16 Serialize(char* buffer, int32 offset) override
	{
		return 0;
	}
	virtual uint16 Deserialize(char* buffer, int32 offset) override
	{
		return 0;
	}
	virtual void Init() override
	{
	}
protected:
	virtual void Destroy() override
	{
	}
};

class NetItemData : public IPacketStruct
{
public:
	int64 InventorySequence		= 0;
	int64 ExpireDate			= 0;
	int32 Index					= 0;
	int32 Quantity				= 0;
	uint8 Level					= 0;
	uint8 EquipState			= 0;

	void Init()
	{
	}

	virtual void Destroy() override
	{
	}

	virtual uint16 Serialize(char* buffer, int32 offset) override
	{
		// simple example code
		uint16 size = 0;
		//size += PacketUtil::Write(buffer, offset + size, InventorySequence);
		//...
		return size;
	}

	virtual uint16 Deserialize(char* buffer, int32 offset) override
	{
		// simple example code
		uint16 size = 0;
		//size += PacketUtil::Read(buffer, offset + size, InventorySequence);
		//...
		return size;
	}
};

class NetAttributeData : public IPacketStruct
{
public:
	int64 ParentsSequence = 0;
	int64 AttributeSequence = 0;
	uint8 AttributeType = 0;
	uint8 AttributeValue = 0;

	void Init()
	{
	}

	virtual void Destroy() override
	{
	}

	virtual uint16 Serialize(char* buffer, int32 offset) override
	{
		// simple example code
		uint16 size = 0;
		//size += PacketUtil::Write(buffer, offset + size, ParentsSequence);
		//...
		return size;
	}

	virtual uint16 Deserialize(char* buffer, int32 offset) override
	{
		// simple example code
		uint16 size = 0;
		//size += PacketUtil::Read(buffer, offset + size, ParentsSequence);
		//...
		return size;
	}
};

static constexpr int32 kItemDefaultPoolSize = 100;
static constexpr int32 kAttributeDefaultPoolSize = 200;

UCLASS()
class SIMPLEGAME_API UTestServer : public UObject
{
	GENERATED_BODY()

	void ServerOpen();
	void ServerClose();

	// not have structure by user
	TArray<NetItemData> ItemDatas;
	TArray<NetAttributeData> AttDatas;
};
