#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Define.generated.h"

static constexpr auto UI_ROOT_LAYER_PATH = "/Game/UI/UMG/Common/W_Master";
static constexpr auto UI_PAGE_RESOURCE_PATH = "UIPage/";
static constexpr auto UI_POPUP_RESOURCE_PATH = "UIPopup/";

static constexpr int32 kDefaultWeaponInventorySize = 20;
static constexpr int32 kDefaultArmorInventorySize = 50;

#define SIMPLE_LOCTEXT(Key) FText::FromStringTable("/Game/DB/StringData/SimpleST.SimpleST", Key)

UENUM(BlueprintType)
enum class EProductSection : uint8
{
	NONE		= 0,
	EXPIRABLE	= 1,
	PERMANENT	= 2,
};

UENUM(BlueprintType)
enum class EProductType : uint8
{
	NONE		= 0	UMETA(DisplayName = "None"),
	WEAPON		= 1	UMETA(DisplayName = "Weapon"),
	ARMOR		= 2	UMETA(DisplayName = "Armor"),
	HELMET		= 3	UMETA(DisplayName = "Helmet"),
	GLOVES		= 4	UMETA(DisplayName = "Gloves"),
	BOOTS		= 5	UMETA(DisplayName = "Boots"),
	CONSUMABLE	= 6	UMETA(DisplayName = "Consumable"),
	QUESTITEM	= 7	UMETA(DisplayName = "Quest Item"),
};

UENUM(BlueprintType)
enum class EAttributeSection : uint8
{
	NONE	= 0,
};

UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	NONE	= 0,
};


UENUM(BlueprintType)
enum class EEquipState : uint8
{
	NONE	= 0,
	EQUIP	= 1,
	UNEQUIP = 2,
};


