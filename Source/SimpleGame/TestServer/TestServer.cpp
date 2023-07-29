// Fill out your copyright notice in the Description page of Project Settings.


#include "TestServer.h"

void UTestServer::ServerOpen()
{
	ItemDatas.Empty();
	AttDatas.Empty();

	ItemDatas.Reserve(kItemDefaultPoolSize);
	AttDatas.Reserve(kAttributeDefaultPoolSize);
}

void UTestServer::ServerClose()
{
	for (NetItemData& It : ItemDatas) {
		It.Destroy();
	}
	for (NetAttributeData& It : AttDatas) {
		It.Destroy();
	}

	ItemDatas.Empty();
	AttDatas.Empty();
}
