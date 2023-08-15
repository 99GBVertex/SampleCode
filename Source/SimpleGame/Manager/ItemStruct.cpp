
#include "ItemStruct.h"
#include "TestServer/Packet.h"

void FItemBase::BindNetData(const FNetItemData& InNetData)
{
	id = InNetData.ID;
	expireDate = InNetData.ExpireDate;
}

void FItemBase::SetTableKey()
{
	nameTableKey = FString::Format(TEXT("Item.{0}.name"), { index });
	descriptTableKey = FString::Format(TEXT("Item.{0}.description"), { index });
}

bool FItemBase::IsExpired() const
{
	if (productData.productSection == EProductSection::EXPIRABLE) {
		const int64 expireTick = FDateTime(expireDate).GetTicks();
		const int64 utcNowTick = FDateTime::UtcNow().GetTicks();
		const bool expired = (expireTick - utcNowTick) <= 0;
		return expired;
	}
	return false;
}

bool FItemBase::IsValid() const
{
	// As DEFAULT_ALIGNMENT is defined to 0 now, I changed that to the original numerical value here
	const int32 AlignmentCheck = MIN_ALIGNMENT - 1;

	// Check 'this' pointer before trying to access any of the Object's members
	if ((this == nullptr) || (UPTRINT)this < 0x100)
	{
		UE_LOG(LogTemp, Error, TEXT("\'this\' pointer is invalid."));
		return false;
	}
	if ((UPTRINT)this & AlignmentCheck)
	{
		UE_LOG(LogTemp, Error, TEXT("\'this\' pointer is misaligned."));
		return false;
	}
	if (*(void**)this == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Virtual functions table is invalid."));
		return false;
	}

	if (id <= 0 || index <= 0) {
		UE_LOG(LogTemp, Error, TEXT("ItemID or Index is invalid."));
		return false;
	}
	return true;
}

TArray<const FAttributeInfo*> FItemBase::GetAttributes() const
{
	TArray<const FAttributeInfo*> outAtts;
	if (attributeList.Num() <= 0) return outAtts;

	for (TSharedPtr<FAttributeInfo> setAttribute : attributeList) {
		if (!setAttribute.IsValid()) continue;
		outAtts.Emplace(setAttribute.Get());
	}
	return outAtts;
}

TWeakPtr<FItemBase> FEquipmentSlot::GetEquipment(EProductType pType)
{
	TWeakPtr<FItemBase> outResult = nullptr;
	switch (pType)
	{
	case EProductType::WEAPON:	outResult = mainWeapon; break;
	case EProductType::ARMOR:	outResult = helmet; break;
	case EProductType::HELMET:	outResult = armer; break;
	case EProductType::GLOVES:	outResult = gloves; break;
	case EProductType::BOOTS:	outResult = boots; break;
	default:
		break;
	}
	return outResult;
}
