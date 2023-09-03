// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Item/Equipment.h"
#include "UI/UMG/Page/InventoryPage.h"
#include "UI/UMG/Item/InventoryItem.h"
#include "Manager/ItemManager.h"
#include "Manager/ItemStruct.h"
#include "UI/UMG/SGButton.h"

void UEquipment::UIConstuctor()
{
	Super::UIConstuctor();
	EquipTable = { {EProductType::WEAPON, EquippedWeapon},
					{EProductType::ARMOR, EquippedHelmet},
					{EProductType::HELMET, EquippedArmor},
					{EProductType::GLOVES, EquippedGloves},
					{EProductType::BOOTS, EquippedBoots} };

	for (const TPair<EProductType, TObjectPtr<UInventoryItem>>& kvp : EquipTable)
	{
		TObjectPtr<UInventoryItem> curEquipped = kvp.Value;
		if (IsValid(curEquipped) && IsValid(curEquipped->GetItemButton())) 
		{
			TObjectPtr<USGButton> currentItemButton = curEquipped->GetItemButton();
			currentItemButton->OnClickedReturnSelf.AddUniqueDynamic(this, &ThisClass::OnClieckedEquippedSlot);
		}
	}
}

void UEquipment::UIDestructor()
{
	for (const TPair<EProductType, TObjectPtr<UInventoryItem>>& kvp : EquipTable)
	{
		TObjectPtr<UInventoryItem> curEquipped = kvp.Value;
		if (IsValid(curEquipped) && IsValid(curEquipped->GetItemButton()))
		{
			TObjectPtr<USGButton> currentItemButton = curEquipped->GetItemButton();
			if (currentItemButton->OnClickedReturnSelf.Contains(this, "OnClieckedEquippedSlot")) {
				currentItemButton->OnClickedReturnSelf.RemoveDynamic(this, &ThisClass::OnClieckedEquippedSlot);
			}
		}
	}
}

void UEquipment::SetRoot(const TObjectPtr<UInventoryPage>& InRootPage)
{
	RootPage = InRootPage;
}

void UEquipment::SetEquipment()
{
	const TWeakPtr<const FEquipmentSlot> curEquipmentSlot = UItemManager::Instance()->GetEquipment(kDefaultSlotIdx);
	bool bSlotInvalid = false;
	if (!curEquipmentSlot.IsValid()) {
		bSlotInvalid = true;
	}

	TArray<EProductType> showEquipmentTypes = { EProductType::WEAPON,
											EProductType::ARMOR,
											EProductType::HELMET,
											EProductType::GLOVES,
											EProductType::BOOTS };

	for (EProductType showEquipmentType : showEquipmentTypes)
	{
		if (!EquipTable.Contains(showEquipmentType) || !IsValid(EquipTable[showEquipmentType])) {
			// log warning
			continue;
		}

		TObjectPtr<UInventoryItem> curMatchedUI = EquipTable[showEquipmentType];
		if (bSlotInvalid || !curEquipmentSlot.Pin()->IsEquipment(showEquipmentType)) {
			curMatchedUI->SetDefault(showEquipmentType);
		}
		else {
			const TWeakPtr<const FItemBase> curEquipment = curEquipmentSlot.Pin()->GetEquipment(showEquipmentType);
			curMatchedUI->SetInventoryItem(curEquipment);
		}
	}
}

void UEquipment::OnClieckedEquippedSlot(UWidget* clickedWidget)
{
	for (const TPair<EProductType, TObjectPtr<UInventoryItem>>& kvp : EquipTable) 
	{
		TObjectPtr<UInventoryItem> curEquipped = kvp.Value;
		if (IsValid(curEquipped) && curEquipped->GetItemButton() == clickedWidget)
		{
			const TWeakPtr<const FItemBase> cachedItem = curEquipped->GetCachedItemInfo();
			const bool bUpdatedDetach = UItemManager::Instance()->UpdateItemImmediately(cachedItem, EEquipState::UNEQUIP);
			if (!bUpdatedDetach) {
				return;
			}

			if (RootPage) {
				RootPage->EquipmentEquipStateChanged(this);
			}

			const TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController();
			if (IsValid(PlayerController))
			{
				const TObjectPtr<ASwordManCharacter> swordMan = Cast<ASwordManCharacter>(PlayerController->GetCharacter());
				if (IsValid(swordMan)) {
					swordMan->DetachWeaponMesh();
				}
			}

#ifdef ADDTOSCREEN_DEBUGMESSAGE
			const FString displayLog = FString::Format(TEXT("{0} {1}"), { cachedItem.Pin()->GetName().ToString(), SIMPLE_LOCSTRING(TEXT("useraction.inventory.detach")) });
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, displayLog, true, { 2.f, 2.f });
#endif
		}
	}
}

