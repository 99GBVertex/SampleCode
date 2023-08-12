// Fill out your copyright notice in the Description page of Project Settings.

#include "FSM.h"
#include "Tickable.h"

UFSM::UFSM()
{
}

UFSM::~UFSM()
{
	PreState = nullptr;
	CurrentState = nullptr;
}

void UFSM::Release()
{
	if (IsValid(CurrentState))
	{
		Cast<UState>(CurrentState)->EndState();
	}
}

void UFSM::Tick(float DeltaTime)
{
	if (!StateBufferQueue.IsEmpty() && !bStateSetting)
	{
		const UClass* StateClass = nullptr;
		if (StateBufferQueue.Dequeue(StateClass))
		{
			SetState(StateClass);
		}
	}

	// Tick Uncomment When Required
	/*
	if (IsValid(CurrentState))
	{
		if (UState* FsmState = Cast<UState>(CurrentState))
		{
			FsmState->Tick(DeltaTime);
		}
	}
	*/
}

void UFSM::AddState(UObject* State)
{
	check(Cast<UState>(State));

	States.Emplace(State);
}

void UFSM::SetState(const UClass* Class)
{
	if (!IsValid(Class))
	{
		return;
	}

	for (auto i : States)
	{
		if (i->GetClass() == Class
			|| i->GetClass()->IsChildOf(Class))
		{
			if (CurrentState && CurrentState == i)
			{
				return;
			}

			if (bStateSetting)
			{
				StateBufferQueue.Enqueue(Class);

				return;
			}

			if (IsValid(CurrentState))
			{
				UState* CurrentInterfaceState = Cast<UState>(CurrentState);
				CurrentInterfaceState->UnregisterDelegates();
				CurrentInterfaceState->EndState();
				CurrentInterfaceState->UnBindEventCalls();
			}

			PreState = CurrentState;
			CurrentState = i;

			if (NaviStateStack.Num() > 1 && CurrentState == NaviStateStack.Last(1))
			{
				NaviStateStack.Pop();
			}
			else
			{
				NaviStateStack.Emplace(CurrentState);
			}

			bStateSetting = true;

			UState* CurrentInterfaceState = Cast<UState>(CurrentState);
			CurrentInterfaceState->RegisterDelegates();
			CurrentInterfaceState->StartState();
			CurrentInterfaceState->BindEventCalls();

			bStateSetting = false;

			return;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("UFSM %s is InValid Class"), *Class->GetName());
	check(0);
}

UObject* UFSM::GetCurrentState() const
{
	return CurrentState;
}

UClass* UFSM::GetCurrentStateClass() const
{
	if (IsValid(CurrentState))
	{
		return CurrentState->GetClass();
	}

	return nullptr;
}

UObject* UFSM::GetPreState() const
{
	return PreState;
}

UClass* UFSM::GetPreStateClass() const
{
	if (IsValid(PreState))
	{
		return PreState->GetClass();
	}

	return nullptr;
}

UClass* UFSM::GetPreNaviStateClass() const
{
	if (NaviStateStack.Num() > 1)
	{
		return NaviStateStack.Last(1)->GetClass();
	}

	return nullptr;
}

UObject* UFSM::FindStateByClass(UClass* TargetClass) const
{
	UObject* const* TargetState = States.FindByPredicate([TargetClass](UObject* State) {
		return State->GetClass() == TargetClass;
		});

	return TargetState ? *TargetState : nullptr;
}

