#pragma once

#include "CoreMinimal.h"
#include "EventManager.generated.h"

class UState;
class USimpleMsgUserWidget;
struct FEventMessage;
enum class EEventType : uint8;

typedef TSharedPtr<FEventMessage, ESPMode::ThreadSafe> EventMsgPtr;

DECLARE_MULTICAST_DELEGATE_TwoParams(FEventCall, EEventType, EventMsgPtr);
typedef TSharedPtr<FEventCall, ESPMode::ThreadSafe> EventCall;


UCLASS()
class SIMPLEGAME_API UEventManager : public UObject
{
	GENERATED_BODY()

public:
	void Init();
	void Release();

public:
	void AddStateReceiver(const TObjectPtr<UState>& Handler, const TArray<EEventType> bindTypes);
	void RemoveStateReceiver(const TObjectPtr<UState>& Handler, const TArray<EEventType> bindTypes);

	void AddUIReceiver(const TObjectPtr<USimpleMsgUserWidget>& Handler, const TArray<EEventType> bindTypes);
	void RemoveUIReceiver(const TObjectPtr<USimpleMsgUserWidget>& Handler, const TArray<EEventType> bindTypes);

	void CallEvent(EEventType eventType, const TSharedPtr<FEventMessage>& msg = nullptr);

private:
	TMap<EEventType, EventCall> StateEventPool;
};