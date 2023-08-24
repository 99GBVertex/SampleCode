#pragma once

#include "CoreMinimal.h"
#include "EventType.generated.h"

UENUM()
enum class EEventType : uint8
{
	msg_rpl_hello,
	msg_rpl_Inventory,
	msg_rpl_changeequip,

	MAX
};
ENUM_RANGE_BY_COUNT(EEventType, EEventType::MAX);

USTRUCT()
struct SIMPLEGAME_API FEventMessage
{
	GENERATED_BODY()

};