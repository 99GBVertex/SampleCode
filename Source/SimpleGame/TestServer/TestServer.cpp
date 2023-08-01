// Fill out your copyright notice in the Description page of Project Settings.


#include "TestServer.h"
#include "Manager/NetworkManager.h"

void UTestServer::Tick(float DeltaTime)
{
	if (!packets.IsEmpty()) {
		const SimplePacket* curPacket;
		packets.Dequeue(curPacket);

		AsyncTask(ENamedThreads::GameThread, [this, curPacket]() {
			this->Dispatch(curPacket);
		});
	}
}

TStatId UTestServer::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UTestServer, STATGROUP_Tickables);
}

void ServerReflectHello(const SimplePacket* qryPacket)
{
	
}

void UTestServer::Dispatch(const SimplePacket* qryPacket)
{
	if(!qryPacket) return;

	ProtocolId protocolId = qryPacket->protocolId;
	switch (protocolId)
	{
	case QryHello:
	{
		const QrySimpleHello* qryHello = dynamic_cast<const QrySimpleHello*>(qryPacket);
		if (qryHello) {
			RplSimpleHello* helloInfo = new RplSimpleHello();
			helloInfo->protocolId = ProtocolId::RplHello;
			helloInfo->accountTocken = 2313549687122;

			UNetworkManager::Instance()->Dispatch(helloInfo->protocolId, helloInfo);
		}
	}
	break;

	case QryGetInventory:
	{
		const QrySimpleGetInventory* qryInventory = dynamic_cast<const QrySimpleGetInventory*>(qryPacket);
		if (qryInventory) {
			RplSimpleGetInventory* rplInven = new RplSimpleGetInventory();
			rplInven->protocolId = ProtocolId::RplGetInventory;
			FillUserInventory(rplInven->NetItemDatas, rplInven->NetAttDatas);

			UNetworkManager::Instance()->Dispatch(rplInven->protocolId, rplInven);
		}
	}
	break;

	case None:
	default:
		break;
	}

	delete qryPacket;
	qryPacket = nullptr;
}

bool UTestServer::FillUserInventory(TArray<NetItemData>& refItemDatas, TArray<NetAttributeData>& refAttDatas)
{
	refItemDatas.Empty();
	refAttDatas.Empty();

	refItemDatas.Append(ItemDatas);
	refAttDatas.Append(AttDatas);

	return true;
}

void UTestServer::ServerOpen()
{
	ItemDatas.Empty();
	AttDatas.Empty();
	ItemDatas.Reserve(kItemDefaultPoolSize);
	AttDatas.Reserve(kAttributeDefaultPoolSize);

	NetItemData swordA;
	swordA.ID = 21322211;
	swordA.Index = 1100001;
	swordA.Quantity = 1;
	swordA.Level = 1;
	swordA.EquipState = 2;
	swordA.ExpireDate = 0;

	NetItemData swordB;
	swordB.ID = 21322212;
	swordB.Index = 1100002;
	swordB.Quantity = 1;
	swordB.Level = 1;
	swordB.EquipState = 2;
	swordB.ExpireDate = 0;

	NetItemData swordC;
	swordC.ID = 21322213;
	swordC.Index = 1100003;
	swordC.Quantity = 1;
	swordC.Level = 1;
	swordC.EquipState = 2;
	swordC.ExpireDate = 0;

	ItemDatas.Append({ swordA, swordB, swordC });

	bAllowedToTick = true;
}

void UTestServer::ServerClose()
{
	bAllowedToTick = false;

	ItemDatas.Empty();
	AttDatas.Empty();
}

void UTestServer::AddBuffer(const SimplePacket* packet)
{
	packets.Enqueue(packet);
}
