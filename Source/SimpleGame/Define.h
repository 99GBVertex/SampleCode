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
	NONE,
	EXPIRABLE,
	PERMANENT,
};

UENUM(BlueprintType)
enum class EProductType : uint8
{
	NONE UMETA(DisplayName = "None"),
	WEAPON UMETA(DisplayName = "Weapon"),
	ARMOR UMETA(DisplayName = "Armor"),
	HELMET UMETA(DisplayName = "Helmet"),
	GLOVES UMETA(DisplayName = "Gloves"),
	BOOTS UMETA(DisplayName = "Boots"),
	CONSUMABLE UMETA(DisplayName = "Consumable"),
	QUESTITEM UMETA(DisplayName = "Quest Item"),
};

UENUM(BlueprintType)
enum class EAttributeSection : uint8
{
	NONE,
};

UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	NONE,
};


