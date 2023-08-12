#include "EventManager.h"
#include "Define.h"
#include "EventType.h"
#include "DesignPattern/State.h"

void UEventManager::Init()
{
	StateEventPool.Empty();
	StateEventPool.Reserve(GET_ENUM_COUNT(EEventType));
	for (EEventType Iter : TEnumRange<EEventType>()) {
		StateEventPool.Emplace(Iter, MakeShared<FEventStateCall, ESPMode::ThreadSafe>());
	}
	UE_LOG(LogTemp, Display, TEXT(""));
}

void UEventManager::Release()
{
	StateEventPool.Empty();
}

void UEventManager::AddReceiver(const TObjectPtr<UState>& Handler, const TArray<EEventType> bindTypes)
{
	for (EEventType bindType : bindTypes)
	{
		StateEventCall TempHandler = StateEventPool[bindType];
		if (!TempHandler->IsBoundToObject(Handler))
		{
			TempHandler->AddUObject(Handler, &UState::OnBoundEventBroadCast);
		}
		UE_LOG(LogTemp, Display, TEXT("Add UState [%s]"), *Handler->GetName());
	}
}

void UEventManager::RemoveReceiver(const TObjectPtr<UState>& Handler, const TArray<EEventType> bindTypes)
{
	for (EEventType bindType : bindTypes)
	{
		StateEventCall TempHandler = StateEventPool[bindType];
		if (TempHandler->IsBoundToObject(Handler))
		{
			TempHandler->RemoveAll(Handler);
		}
		UE_LOG(LogTemp, Display, TEXT("Remove UU2MenuButton [%s]"), *Handler->GetName());
	}
}

void UEventManager::CallEvent(EEventType eventType, const TSharedPtr<FEventMessage>& msg/* = nullptr*/)
{
	if(StateEventPool.Num() == 0) return;

	if (StateEventPool.Contains(eventType)) 
	{
		StateEventCall curEvent = StateEventPool[eventType];
		if (curEvent.IsValid() && curEvent->IsBound()) {
			curEvent->Broadcast(eventType, msg);
		}
	}
}
