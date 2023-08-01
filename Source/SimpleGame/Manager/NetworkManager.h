// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestServer/TestServer.h"
#include "DesignPattern/Singleton.h"
#include <map>
#include <functional>
#include "NetworkManager.generated.h"

class UTestServer;
class NetItemData;
class NetAttributeData;

/**
 *
 */
UCLASS()
class SIMPLEGAME_API UNetworkManager : public UObject, public FSingleton<UNetworkManager>
{
	GENERATED_BODY()

public:

	void SendHello();
	void SendGetInventory();

	void Init();
	void Release();
	void Bind(ProtocolId packetType, void(*handler)(const SimplePacket*));
	bool Dispatch(ProtocolId packetType, const SimplePacket* packet);
	bool NetWorkResultCodeCheck(ProtocolId InProtocolID, uint16 InResultCode);

private:
	void SetNetworkEvent();

private:
	UTestServer* testServer;
	std::map<ProtocolId, std::function<void(const SimplePacket*)>> net_handlers;
};
