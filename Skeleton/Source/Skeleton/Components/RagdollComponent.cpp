#include "RagdollComponent.h"

#include "Components/SkeletalMeshComponent.h"


URagdollComponent::URagdollComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}

void URagdollComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void URagdollComponent::Init()
{
	World = GetWorld();
	
	AActor* Owner = GetOwner();
	if (!Owner) return;

	TArray<UActorComponent*> RagdollsActorComponents = Owner->GetComponentsByTag(USkeletalMeshComponent::StaticClass(),FName("ragdoll"));
	TArray<UActorComponent*> PhysicsActorComponents = Owner->GetComponentsByTag(UStaticMeshComponent::StaticClass(),FName("physics"));
	
	if (RagdollsActorComponents.Num() == 0) return;
	if (PhysicsActorComponents.Num() == 0) return;
	
	for (auto ActorComponent : RagdollsActorComponents)
	{
		if (ActorComponent)
		{
			USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(ActorComponent);
			if (SkeletalMeshComponent)
			{
				SkeletalMeshComponents.Add(SkeletalMeshComponent);
			}
		}
	}

	for (auto ActorComponent : PhysicsActorComponents)
	{
		if (ActorComponent)
		{
			UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(ActorComponent);
			if (StaticMeshComponent)
			{
				StaticMeshComponents.Add(StaticMeshComponent);
			}
		}
	}
}

void URagdollComponent::SetLeaderPoseComponent()
{
	if (!World) return;
	
	if (SkeletalMeshComponents.Num() == 0) return;
	if (StaticMeshComponents.Num() == 0) return;
	
	for (auto SkeletalMeshComponent : SkeletalMeshComponents)
	{
		if (SkeletalMeshComponent)
		{
			SkeletalMeshComponent->SetLeaderPoseComponent(nullptr);
		}
	}
	
	FTimerHandle TimerCoolDown;
	World->GetTimerManager().SetTimer(TimerCoolDown, [&]()
	{
		for (auto SkeletalMeshComponent : SkeletalMeshComponents)
		{
			if (SkeletalMeshComponent)
			{
				SkeletalMeshComponent->SetSimulatePhysics(true);
			}
		}

		for (auto StaticMeshComponent : StaticMeshComponents)
		{
			if (StaticMeshComponent)
			{
				StaticMeshComponent->SetSimulatePhysics(true);
			}
		}
		
	}, PhysicsDelay, false);

}
