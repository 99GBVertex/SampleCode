#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Define.generated.h"

static constexpr auto UI_ROOT_LAYER_PATH = "/Game/UI/UMG/Common/W_Master";
static constexpr auto UI_PAGE_RESOURCE_PATH = "/Game/UI/UMG/Page/";
static constexpr auto UI_POPUP_RESOURCE_PATH = "/Game/UI/UMG/Popup/";
static constexpr auto UI_SYSTEM_POPUP_RESOURCE_PATH = "/Game/UI/UMG/SystemPopup/";
static constexpr auto UI_UMG_ATLAS_RESOURCE_PATH = "/Game/UI/Art/Atlas/Sprite/";
static constexpr auto TARGET_CANVAS_NAME = TEXT("UICanvas");

static constexpr int32 kDefaultWeaponInventorySize = 20;
static constexpr int32 kDefaultArmorInventorySize = 50;

#define SIMPLE_LOCTEXT(Key) FText::FromStringTable("/Game/DB/StringData/SimpleST.SimpleST", Key)

#define GET_ENUM_STRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetNameStringByIndex((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )
#define GET_ENUM_COUNT(etype) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(#etype), true) != nullptr ) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(#etype), true)->NumEnums() - 1 : -1 )
#define CONCAT(X,Y) X##Y

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
	MAX				UMETA(Hidden),
};
ENUM_RANGE_BY_COUNT(EProductType, EProductType::MAX);

UENUM(BlueprintType)
enum class EProductGrade : uint8
{
	NONE		= 0	UMETA(DisplayName = "None"),
	NORMAL		= 1	UMETA(DisplayName = "Normal"),
	RARE		= 2	UMETA(DisplayName = "Rare"),
	UNIQUE		= 3	UMETA(DisplayName = "Unique"),
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
	NONE	= 0	UMETA(DisplayName = "None"),
	EQUIP	= 1	UMETA(DisplayName = "Equipped"),
	UNEQUIP = 2	UMETA(DisplayName = "UnEquipped"),
};


