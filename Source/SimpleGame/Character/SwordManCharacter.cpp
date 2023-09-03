// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordManCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"

#include "Manager/ItemManager.h"
#include "DesignPattern/FSM.h"
#include "AI/AISwordMan.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Character/State/SwordManState_Idle.h"

// Sets default values
ASwordManCharacter::ASwordManCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		PrimaryActorTick.bCanEverTick = true;
		PrimaryActorTick.bStartWithTickEnabled = true;

		IKHandL = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftHandPoint"));
		IKHandR = CreateDefaultSubobject<UArrowComponent>(TEXT("RightHandPoint"));
		IKWeaponPointL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWeaponPoint"));
		IKWeaponPointR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWeaponPoint"));

		IKHandL->SetupAttachment(GetMesh());
		IKWeaponPointL->SetupAttachment(IKHandL);
		IKHandR->SetupAttachment(GetMesh());
		IKWeaponPointR->SetupAttachment(IKHandR);
	}
}

// Called when the game starts or when spawned
void ASwordManCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitFSM();
	InitAnimInstance();
}

// Called every frame
void ASwordManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASwordManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASwordManCharacter::InitFSM()
{
	Super::InitFSM();

	FSM_ADDSTATE(CharacterFSM, USwordManState_Idle);
	this->OnStateChanged.Broadcast(USwordManState_Idle::StaticClass());
}

void ASwordManCharacter::InitAnimInstance()
{
	if (!RootComponent) {
		// log Init Error
		return;
	}
	SwordManSKMesh = GetMesh();
	ensure(IsValid(SwordManSKMesh));

	SwordManAI = Cast<UAISwordMan>(SwordManSKMesh->GetAnimInstance());
	ensure(IsValid(SwordManAI));

	SwordManAI->Init();

	FName LeftHandSocketName = TEXT("LeftHand");
	IKHandL->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandSocketName);
	FTransform lkWeaponRelativeTransformL{
	FRotator{90.f, 0.f, 0.f},	// Rotation
	FVector{2.f, -8.f, 2.f},	// Translation
	FVector{.5f, .5f, .5f}		// Scale
	};
	IKHandL->SetRelativeTransform(lkWeaponRelativeTransformL);

	FName RightHandSocketName = TEXT("RightHand");
	IKHandR->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandSocketName);
	FTransform lkWeaponRelativeTransformR{
				FRotator{90.f, 0.f, 0.f},	// Rotation
				FVector{2.f, -8.f, 2.f},	// Translation
				FVector{.5f, .5f, .5f}		// Scale
	};
	IKHandR->SetRelativeTransform(lkWeaponRelativeTransformR);

}

void ASwordManCharacter::AttachWeaponMesh(const TWeakPtr<const FItemBase> targetWeapon)
{
	if (!IsValid(IKWeaponPointR))
		return;
	if(!targetWeapon.IsValid() || !targetWeapon.Pin()->IsValid()) {
		// set default Weapon
		AttachWeaponMesh(kDefaultWeaponIndex);
		return;
	}
	TWeakPtr<const FWeapon> curWeapon = StaticCastWeakPtr<const FWeapon>(targetWeapon);
	if (!curWeapon.IsValid()) {
		return;
	}
	TObjectPtr<UStaticMesh> targetMesh = curWeapon.Pin()->resourceData.mesh_Optr.LoadSynchronous();
	if (IKWeaponPointR->GetStaticMesh() != targetMesh)
	{
		FTransform offset = curWeapon.Pin()->resourceData.mesh_ik_offset;
		IKWeaponPointR->SetStaticMesh(targetMesh);
		IKWeaponPointR->SetRelativeTransform(offset);

		TObjectPtr<UNiagaraSystem> nsEffect = curWeapon.Pin()->resourceData.item_effect_Optr.LoadSynchronous();
		TObjectPtr<UNiagaraComponent> rWeaponEffComp = nullptr;
		const int nscIdx = IKWeaponPointR->GetAttachChildren().IndexOfByPredicate([](const TObjectPtr<USceneComponent>& row) {
			return row->IsA<UNiagaraComponent>();
			});
		if (IsValid(nsEffect) && nscIdx == -1) {
			rWeaponEffComp = UNiagaraFunctionLibrary::SpawnSystemAttached(nsEffect, IKWeaponPointR, "", FVector(0, 0, 0), FRotator(0, 0, 0), EAttachLocation::SnapToTarget, true);
		}
		else {
			rWeaponEffComp = Cast<UNiagaraComponent>(IKWeaponPointR->GetChildComponent(nscIdx));
		}

		if (IsValid(rWeaponEffComp))
		{
			if (rWeaponEffComp->GetAsset() != nsEffect) {
				rWeaponEffComp->SetAsset(nsEffect);
			}
			// set asset nullptr will be dstroyInstance self
			rWeaponEffComp->Activate();
		}
	}
}

void ASwordManCharacter::DetachWeaponMesh()
{
	AttachWeaponMesh(nullptr);
}

void ASwordManCharacter::AttachWeaponMesh(int32 itemIndex)
{
	TObjectPtr<const FItemTable> itemTableData = UItemManager::Instance()->GetItemData(itemIndex);
	if (!itemTableData || !itemTableData->item_mesh_Optr.IsNull()) {
		// log Warning
		return;
	}
	TSharedPtr<FWeapon> dummyItem;
	if (UItemManager::Instance()->CreateWeapon(itemIndex, dummyItem)) {
		AttachWeaponMesh(dummyItem);
	}
	else {
		// log Warning
	}
}
