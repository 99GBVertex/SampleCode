// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/AISwordMan.h"
#include "Animation/AnimMontage.h"

void UAISwordMan::Init()
{
	speed = 0.f;
	bMontaging = false;
}


void UAISwordMan::Release()
{
	
}

void UAISwordMan::SG_Idle_ChangeWeapon_Implementation() {}
