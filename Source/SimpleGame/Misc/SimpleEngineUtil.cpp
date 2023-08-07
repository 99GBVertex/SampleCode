// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/SimpleEngineUtil.h"

UWorld* SimpleEngineUtil::ModeWorld = nullptr;
FName SimpleEngineUtil::LandscapeProfileName = "LandscapeProfile";

UWorld* GetModeWorld()
{
	return SimpleEngineUtil::ModeWorld;
}

SimpleEngineUtil::SimpleEngineUtil()
{
}

SimpleEngineUtil::~SimpleEngineUtil()
{
}
