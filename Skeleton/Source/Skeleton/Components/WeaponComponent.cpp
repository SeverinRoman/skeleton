#include "WeaponComponent.h"

#include "WeaponLeftType.h"
#include "WeaponRightType.h"


UWeaponComponent::UWeaponComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UWeaponComponent::Init()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;
	
	RightHandWeapons.Add(EWeaponRightType::SWORD ,Owner->FindComponentByTag<UStaticMeshComponent>("sword"));

	SetWeaponHandRight(StartWeaponHandRight);
	SetWeaponHandLeft(StartWeaponHandLeft);

	UE_LOG(LogTemp, Warning, TEXT("UWeaponComponent::ClearWeaponHandRight 0"));
}

void UWeaponComponent::SetWeaponHandRight(EWeaponRightType NewWeaponRightType)
{
	UE_LOG(LogTemp, Warning, TEXT("UWeaponComponent::ClearWeaponHandRight 1"));
	
	if (EWeaponRightType::NONE == NewWeaponRightType) return;
	if (CurrentWeaponHandRight == NewWeaponRightType) return;

	if (EWeaponRightType::FIST == NewWeaponRightType)
	{
		ClearWeaponHandRight();
		CurrentWeaponHandRight = EWeaponRightType::FIST;
		return;
	}
	if (!RightHandWeapons.Contains(NewWeaponRightType)) return;
	
	ClearWeaponHandRight();
	RightHandWeapons[NewWeaponRightType]->SetVisibility(true);

	CurrentWeaponHandRight = NewWeaponRightType;
}

void UWeaponComponent::SetWeaponHandLeft(EWeaponLeftType NewWeaponLeftType)
{
	if (EWeaponLeftType::NONE == NewWeaponLeftType) return;
	if (CurrentWeaponHandLeft == NewWeaponLeftType) return;

	if (EWeaponLeftType::FIST == NewWeaponLeftType)
	{
		ClearWeaponHandLeft();
		CurrentWeaponHandLeft = EWeaponLeftType::FIST;
		return;
	}
	if (!LeftHandWeapons.Contains(NewWeaponLeftType)) return;
	
	ClearWeaponHandLeft();
	LeftHandWeapons[NewWeaponLeftType]->SetVisibility(true);

	CurrentWeaponHandLeft = NewWeaponLeftType;
}

void UWeaponComponent::ClearWeaponHandRight()
{
	UE_LOG(LogTemp, Warning, TEXT("UWeaponComponent::ClearWeaponHandRight 2"));
	
	if (RightHandWeapons.Num() == 0) return;

	UE_LOG(LogTemp, Warning, TEXT("UWeaponComponent::ClearWeaponHandRight 3"));
	
	for (auto Element : RightHandWeapons)
	{
		Element.Value->SetVisibility(false);
	}
}

void UWeaponComponent::ClearWeaponHandLeft()
{
	if (LeftHandWeapons.Num() == 0) return;
	
	for (auto Element : LeftHandWeapons)
	{
		Element.Value->SetVisibility(false);
	}
}



