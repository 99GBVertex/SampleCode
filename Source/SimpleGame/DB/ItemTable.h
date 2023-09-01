#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Define.h"
#include "PaperSpriteAtlas.h"
#include "NiagaraSystem.h"
#include "ItemTable.generated.h"


USTRUCT()
struct SIMPLEGAME_API FItemTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemTable() {}
	~FItemTable() {}

	UPROPERTY(EditAnywhere, Category = "Item")
		int32 index = 0;

	UPROPERTY(EditAnywhere, Category = "Item")
		EProductSection itemSection = EProductSection::NONE;

	UPROPERTY(EditAnywhere, Category = "Item")
		EProductType itemType = EProductType::NONE;

	UPROPERTY(EditAnywhere, Category = "Item")
		EProductGrade itemGrade = EProductGrade::NONE;

	UPROPERTY(EditAnywhere, Category = "Item")
		TSoftObjectPtr<UPaperSprite> item_sprite_Optr;

	UPROPERTY(EditAnywhere, Category = "Item")
		TSoftObjectPtr<UStaticMesh> item_mesh_Optr;

	UPROPERTY(EditAnywhere, Category = "Item")
		FTransform item_mesh_ik_offset;

	UPROPERTY(EditAnywhere, Category = "Item")
		TSoftObjectPtr<UNiagaraSystem> item_effect_Optr;
};
