// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestServer/TestServer.h"
#include "DesignPattern/Singleton.h"
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
};
