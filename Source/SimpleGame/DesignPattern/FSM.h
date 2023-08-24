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
private:
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { return Super::GetStatID(); }
	bool bAllowTickable = false;
	virtual bool IsAllowedToTick() const override { return bAllowTickable; }
	//~ End FTickableGameObject
public:

	void Init();
	void Release();

	void AddState(TObjectPtr<UObject> State);
	void SetState(TObjectPtr<const UClass> Class);

	TObjectPtr<UObject> GetCurrentState() const;
	template <typename StateType>
	TObjectPtr<StateType> GetCurrentState() const;

	TObjectPtr<UClass> GetCurrentStateClass() const;

	TObjectPtr<UObject> GetPreState() const;
	template <typename StateType>
	TObjectPtr<StateType> GetPreState() const;

	TObjectPtr<UClass> GetPreStateClass() const;

	TObjectPtr<UClass> GetPreNaviStateClass() const;
	TObjectPtr<UObject> FindStateByClass(TObjectPtr<UClass> TargetClass) const;
	TArray<TObjectPtr<UObject>> GetAllState() { return States; }

protected:
	UPROPERTY() TObjectPtr<UObject> PreState = nullptr;
	UPROPERTY() TObjectPtr<UObject> CurrentState = nullptr;

	UPROPERTY() TArray<TObjectPtr<UObject>> NaviStateStack;
	UPROPERTY() TArray<TObjectPtr<UObject>> States;
	TQueue<TObjectPtr<const UClass>> StateBufferQueue;

	bool bStateSetting = false;
};

template <typename StateType>
TObjectPtr<StateType> UFSM::GetCurrentState() const
{
	if (IsValid(CurrentState))
	{
		return Cast<StateType>(CurrentState);
	}

	return nullptr;
}

template <typename StateType>
TObjectPtr<StateType> UFSM::GetPreState() const
{
	if (IsValid(PreState))
	{
		return Cast<StateType>(PreState);
	}

	return nullptr;
}