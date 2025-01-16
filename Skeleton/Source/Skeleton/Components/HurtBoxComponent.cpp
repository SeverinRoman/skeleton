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
	
	TArray<UActorComponent*> ActorComponents = Owner->GetComponentsByTag(UShapeComponent::StaticClass(), TagHurtBox);
	if (ActorComponents.Num() == 0) return;

	for (UActorComponent* ActorComponent : ActorComponents)
	{
		if (ActorComponent)
		{
			HurtBoxes.Add(Cast<UShapeComponent>(ActorComponent));
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
			HurtBox->SetHiddenInGame(!IsVisible);
		}
	}
}

