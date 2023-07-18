#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PaperSpriteAtlas.h"
#include "ItemTable.generated.h"

USTRUCT()
struct SIMPLEGAME_API FItemTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemTable() {}
	~FItemTable() {}

	UPROPERTY(EditAnywhere)
		int32 index = 0;

	UPROPERTY(EditAnywhere)
		TSoftObjectPtr<UPaperSprite> item_sprite_Optr;

	UPROPERTY(EditAnywhere)
		TSoftObjectPtr<UStaticMesh> item_mesh_Optr;
};
