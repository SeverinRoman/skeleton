#include "PhysicsHelperComponent.h"

#include "AnimationComponent.h"

#include "Components/SkeletalMeshComponent.h"


UPhysicsHelperComponent::UPhysicsHelperComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}

void UPhysicsHelperComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UPhysicsHelperComponent::Init()
{
	World = GetWorld();
	Owner = GetOwner();

	if (Owner)
	{
		AnimationComponent = Owner->GetComponentByClass<UAnimationComponent>();
	}
	
	InitSkeletalMesh();
	InitStaticMesh();
}

void UPhysicsHelperComponent::InitSkeletalMesh()
{
	if (!Owner) return;
	
	TArray<UActorComponent*> ActorComponents = Owner->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), TagSkeletalMesh);
	if (ActorComponents.Num() == 0) return;

	for (auto ActorComponent : ActorComponents)
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
}

void UPhysicsHelperComponent::InitStaticMesh()
{
	if (!Owner) return;
	
	TArray<UActorComponent*> ActorComponents = Owner->GetComponentsByTag(UStaticMeshComponent::StaticClass(), TagStaticMesh);
	if (ActorComponents.Num() == 0) return;

	for (auto ActorComponent : ActorComponents)
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

void UPhysicsHelperComponent::EnablePhysics()
{
	SetLeaderPoseComponents(nullptr);
	
	if (!World) return;
	World->GetTimerManager().SetTimer(PhysicsDelayTimerHandle, [&]()
	{
		EnablePhysicsSkeletalMesh();
		EnablePhysicsStaticMesh();

		if (AnimationComponent)
		{
			AnimationComponent->Pause();
		}
		
	}, PhysicsDelay, false);
}

void UPhysicsHelperComponent::SetLeaderPoseComponents(USkinnedMeshComponent* NewLeaderBoneComponent)
{
	if (SkeletalMeshComponents.Num() == 0) return;
	
	for (auto SkeletalMeshComponent : SkeletalMeshComponents)
	{
		if (SkeletalMeshComponent)
		{
			SkeletalMeshComponent->SetLeaderPoseComponent(NewLeaderBoneComponent);
		}
	}
}

void UPhysicsHelperComponent::EnablePhysicsSkeletalMesh()
{
	if (SkeletalMeshComponents.Num() == 0) return;

	for (auto SkeletalMeshComponent : SkeletalMeshComponents)
	{
		if (SkeletalMeshComponent)
		{
			SkeletalMeshComponent->SetSimulatePhysics(true);
		}
	}
}

void UPhysicsHelperComponent::EnablePhysicsStaticMesh()
{
	if (StaticMeshComponents.Num() == 0) return;

	for (auto StaticMeshComponent : StaticMeshComponents)
	{
		if (StaticMeshComponent)
		{
			StaticMeshComponent->SetSimulatePhysics(true);
		}
	}
}

