#pragma once

#include "CoreMinimal.h"
#include "EventType.generated.h"

UENUM()
enum class EEventType : uint8
{
	msg_input_release_nonui,
	msg_rpl_hello,
	msg_rpl_inventory,
	msg_rpl_changeequip,

	COUNT
};
ENUM_RANGE_BY_COUNT(EEventType, EEventType::COUNT);

USTRUCT()
struct SIMPLEGAME_API FEventMessage
{
	GENERATED_BODY()

};