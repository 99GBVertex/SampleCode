// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"
#include "Manager/ItemManager.h"
#include "Manager/GameEvent/EventType.h"
#include "Manager/GameEvent/EventManager.h"
#include "Misc/SimpleEngineUtil.h"

void UNetworkManager::Init()
{
	net_handlers.Empty();
	SetNetworkEvent();

	if (!IsValid(testServer)) {
		testServer = NewObject<UTestServer>();
	}
	testServer->ServerOpen();
}

void UNetworkManager::Release()
{
	if (IsValid(testServer)) {
		testServer->ServerClose();
		testServer = nullptr;
	}
	net_handlers.Empty();
}

void UNetworkManager::Bind(ProtocolId packetType, void(*handler)(const USimplePacket*))
{
	if (net_handlers.Num() == 0 || !net_handlers.Contains(packetType)) {
		net_handlers.Emplace(packetType , handler);
	}
}

bool UNetworkManager::Dispatch(ProtocolId packetType, const USimplePacket* packet)
{
	if (!packet) {
		UE_LOG(LogTemp, Log, TEXT("Invalid Packet: protocol [%d]"), (uint16)packetType);
		return false;
	}
	if (!net_handlers.Contains(packetType))
	{
		UE_LOG(LogTemp, Log, TEXT("Invalid Packet: protocol [%d]"), (uint16)packetType);
		return false;
	}

	auto f = net_handlers[packetType];
	f(packet);

	packet = nullptr;
	return true;
}

bool UNetworkManager::NetWorkResultCodeCheck(ProtocolId InProtocolID, uint16 InResultCode)
{
	NetResultCode ResultCode = (NetResultCode)InResultCode;

	if (ResultCode == NetResultCode::NoError)
	{
		return true;
	}
	return false;
}

void UNetworkManager::SendHello()
{
	UQrySimpleHello* qryPacket = NewObject<UQrySimpleHello>();
	qryPacket->protocolId = ProtocolId::QryHello;
	qryPacket->accountID = 1;
	if(testServer) testServer->AddBuffer(qryPacket);
}

void UNetworkManager::SendGetInventory()
{
	UQrySimpleGetInventory* qryPacket = NewObject<UQrySimpleGetInventory>();
	qryPacket->protocolId = ProtocolId::QryGetInventory;
	if (testServer) testServer->AddBuffer(qryPacket);
}

void OnRplSimpleHello(const USimplePacket* packet)
{
	const URplSimpleHello* rplPacket = Cast<URplSimpleHello>(packet);
	if (rplPacket) {
		int32 headerSize = 0;
		if (UNetworkManager::Instance()->NetWorkResultCodeCheck(rplPacket->protocolId, rplPacket->resultCode))
		{
			EVENT()->CallEvent(EEventType::msg_rpl_hello);
		}
	}
}


void OnRplSimpleGetInventory(const USimplePacket* packet)
{
	const URplSimpleGetInventory* rplPacket = Cast<URplSimpleGetInventory>(packet);
	if (rplPacket) {
		int32 headerSize = 0;
		if (UNetworkManager::Instance()->NetWorkResultCodeCheck(rplPacket->protocolId, rplPacket->resultCode))
		{
			UItemManager::Instance()->BindInventoryData(rplPacket->NetItemDatas, rplPacket->NetAttDatas);
			EVENT()->CallEvent(EEventType::msg_rpl_Inventory);
		}
	}
}


void UNetworkManager::SetNetworkEvent()
{
	Bind(ProtocolId::RplHello, &OnRplSimpleHello);
	Bind(ProtocolId::RplGetInventory, &OnRplSimpleGetInventory);
}