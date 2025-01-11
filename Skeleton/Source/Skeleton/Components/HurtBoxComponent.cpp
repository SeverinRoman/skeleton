#include "HurtBoxComponent.h"

#include "Components/ShapeComponent.h"


UHurtBoxComponent::UHurtBoxComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}

void UHurtBoxComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void UHurtBoxComponent::Init()
{
	Owner = GetOwner();
	if (!Owner) return;
	
	AddHurtBoxes();
	ChangeVisibility(IsDebug);
}

void UHurtBoxComponent::AddHurtBoxes()
{
	if (!Owner) return;
	
	for (auto Element : NameHurtBoxes)
	{
		UActorComponent* ActorComponent = Owner->FindComponentByTag(UShapeComponent::StaticClass(), Element);

		if (ActorComponent)
		{
			UShapeComponent* ShapeComponent = Cast<UShapeComponent>(ActorComponent);
			
			if (ShapeComponent)
			{
				HurtBoxes.Add(ShapeComponent);
			}
		}
	}
}

void UHurtBoxComponent::ChangeVisibility(bool IsVisible)
{
	if (HurtBoxes.Num() == 0) return;

	for (auto HurtBox : HurtBoxes)
	{
		if (HurtBox)
		{
			HurtBox->SetVisibility(IsVisible);
		}
	}
}

