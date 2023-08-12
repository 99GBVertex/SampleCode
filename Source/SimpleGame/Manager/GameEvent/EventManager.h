#pragma once

#include "CoreMinimal.h"
#include "EventManager.generated.h"

class UState;
struct FEventMessage;
enum class EEventType : uint8;

typedef TSharedPtr<FEventMessage, ESPMode::ThreadSafe> EventMsgPtr;

DECLARE_MULTICAST_DELEGATE_TwoParams(FEventStateCall, EEventType, EventMsgPtr);
typedef TSharedPtr<FEventStateCall, ESPMode::ThreadSafe> StateEventCall;


UCLASS()
class SIMPLEGAME_API UEventManager : public UObject
{
	GENERATED_BODY()

public:
	void Init();
	void Release();

public:
	void AddReceiver(const TObjectPtr<UState>& Handler, const TArray<EEventType> bindTypes);
	void RemoveReceiver(const TObjectPtr<UState>& Handler, const TArray<EEventType> bindTypes);
	void CallEvent(EEventType eventType, const TSharedPtr<FEventMessage>& msg = nullptr);

private:
	TMap<EEventType, StateEventCall> StateEventPool;
};