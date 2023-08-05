// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "FSM.generated.h"

// AddState Macro
#define FSM_ADDSTATE(Fsm, StateClass) \
Fsm->AddState(NewObject<StateClass>(this, StateClass::StaticClass(), TEXT(#StateClass)));

UCLASS()
class SIMPLEGAME_API UFSM : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UFSM();
	virtual ~UFSM();

	//~ Begin FTickableGameObject
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { return Super::GetStatID(); }
	//~ End FTickableGameObject

	void Release();

	void AddState(UObject* State);
	void SetState(const UClass* Class);

	UObject* GetCurrentState() const;
	template <typename StateType>
	StateType* GetCurrentState() const;

	UClass* GetCurrentStateClass() const;

	UObject* GetPreState() const;
	template <typename StateType>
	StateType* GetPreState() const;

	UClass* GetPreStateClass() const;

	UClass* GetPreNaviStateClass() const;
	UObject* FindStateByClass(UClass* TargetClass) const;
	TArray<UObject*> GetAllState() { return States; }

protected:
	UPROPERTY() UObject* PreState = nullptr;
	UPROPERTY() UObject* CurrentState = nullptr;

	UPROPERTY() TArray<UObject*> NaviStateStack;
	UPROPERTY() TArray<UObject*> States;
	TQueue<const UClass*> StateBufferQueue;

	bool bStateSetting = false;
};

template <typename StateType>
StateType* UFSM::GetCurrentState() const
{
	if (IsValid(CurrentState))
	{
		return Cast<StateType>(CurrentState);
	}

	return nullptr;
}

template <typename StateType>
StateType* UFSM::GetPreState() const
{
	if (IsValid(PreState))
	{
		return Cast<StateType>(PreState);
	}

	return nullptr;
}