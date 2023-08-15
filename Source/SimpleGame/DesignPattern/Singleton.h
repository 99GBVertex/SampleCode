// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template <typename Type>
struct FSingleton
{
public:
	FSingleton() { Inst = nullptr; }
	virtual ~FSingleton()
	{
		if (Inst)  {
			Inst->RemoveFromRoot();
		}
		Inst = nullptr;
	}

	static Type* Instance()
	{
		if (!Inst)  {
			Inst = NewObject<Type>();
			Inst->AddToRoot();
		}
		return Inst;
	}

protected:
	static Type* Inst;
};

template <typename Type>
Type* FSingleton<Type>::Inst = nullptr;