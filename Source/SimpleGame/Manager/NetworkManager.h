// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestServer/TestServer.h"
#include "DesignPattern/Singleton.h"
#include "NetworkManager.generated.h"

class UTestServer;
struct FNetItemData;
struct FNetAttributeData;

/**
 *
 */
UCLASS()
class SIMPLEGAME_API UNetworkManager : public UObject, public FSingleton<UNetworkManager>
{
	GENERATED_BODY()

public:

	void Init();
	void Release();

	void Bind(ProtocolId packetType, void(*handler)(const USimplePacket*));
	bool Dispatch(ProtocolId packetType, const USimplePacket* packet);
	bool NetWorkResultCodeCheck(ProtocolId InProtocolID, uint16 InResultCode);

	void SendHello();
	void SendGetInventory();
private:
	void SetNetworkEvent();

private:
	UPROPERTY() TObjectPtr<UTestServer> testServer;
	TMap<ProtocolId, TFunction<void(const USimplePacket*)>> net_handlers;
};
