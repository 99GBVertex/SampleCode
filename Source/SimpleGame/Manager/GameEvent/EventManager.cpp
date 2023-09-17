#include "EventManager.h"
#include "Define.h"
#include "EventType.h"
#include "DesignPattern/State.h"
#include "UI/UMG/SimpleMsgUserWidget.h"

void UEventManager::Init()
{
	StateEventPool.Empty();
	const int32 eventEnumCountWithoutCount = GET_ENUM_COUNT(EEventType) - 1;
	StateEventPool.Reserve(eventEnumCountWithoutCount);
	for (EEventType Iter : TEnumRange<EEventType>()) {
		StateEventPool.Emplace(Iter, MakeShared<FEventCall, ESPMode::ThreadSafe>());
	}
	UE_LOG(LogTemp, Display, TEXT(""));
}

void UEventManager::Release()
{
	if (!StateEventPool.IsEmpty()) {
		StateEventPool.Empty();
	}	
}

void UEventManager::AddStateReceiver(const TObjectPtr<UState>& Handler, const TArray<EEventType> bindTypes)
{
	for (EEventType bindType : bindTypes)
	{
		EventCall TempHandler = StateEventPool[bindType];
		if (!TempHandler->IsBoundToObject(Handler))
		{
			TempHandler->AddUObject(Handler, &UState::OnBoundEventBroadCast);
		}
#ifdef EVENTLOG
		UE_LOG(LogTemp, Display, TEXT("Add UState [%s]"), *Handler->GetName());
#endif
	}
}

void UEventManager::RemoveStateReceiver(const TObjectPtr<UState>& Handler, const TArray<EEventType> bindTypes)
{
	for (EEventType bindType : bindTypes)
	{
		EventCall TempHandler = StateEventPool[bindType];
		if (TempHandler->IsBoundToObject(Handler))
		{
			TempHandler->RemoveAll(Handler);
		}
#ifdef EVENTLOG
		UE_LOG(LogTemp, Display, TEXT("Remove UState [%s]"), *Handler->GetName());
#endif
	}
}

void UEventManager::AddUIReceiver(const TObjectPtr<USimpleMsgUserWidget>& Handler, const TArray<EEventType> bindTypes)
{
	for (EEventType bindType : bindTypes)
	{
		EventCall TempHandler = StateEventPool[bindType];
		if (!TempHandler->IsBoundToObject(Handler))
		{
			TempHandler->AddUObject(Handler, &USimpleMsgUserWidget::OnBoundEventBroadCast);
		}
#ifdef EVENTLOG
		UE_LOG(LogTemp, Display, TEXT("Add UMG [%s]"), *Handler->GetName());
#endif
	}
}

void UEventManager::RemoveUIReceiver(const TObjectPtr<USimpleMsgUserWidget>& Handler, const TArray<EEventType> bindTypes)
{
	for (EEventType bindType : bindTypes)
	{
		EventCall TempHandler = StateEventPool[bindType];
		if (TempHandler->IsBoundToObject(Handler))
		{
			TempHandler->RemoveAll(Handler);
		}
#ifdef EVENTLOG
		UE_LOG(LogTemp, Display, TEXT("Remove UMG [%s]"), *Handler->GetName());
#endif
	}
}

void UEventManager::CallEvent(EEventType eventType, const TSharedPtr<FEventMessage>& msg/* = nullptr*/)
{
	if(StateEventPool.Num() == 0) return;

	if (StateEventPool.Contains(eventType)) 
	{
		EventCall curEvent = StateEventPool[eventType];
		if (curEvent.IsValid() && curEvent->IsBound()) {
			curEvent->Broadcast(eventType, msg);
		}
	}
}
