#include "AnimationComponent.h"

#include "AnimationType.h"
#include "LandingAnimationType.h"
#include "StandByAnimationType.h"
#include "SwordAnimationType.h"


UAnimationComponent::UAnimationComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}

void UAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UAnimationComponent::Init()
{
	Owner =	GetOwner();
	if (!Owner) return;
	
	SkeletalMeshComponent = Owner->GetComponentByClass<USkeletalMeshComponent>();
	if (!SkeletalMeshComponent) return;
	
	AnimInstance = SkeletalMeshComponent->GetAnimInstance();


	TArray<UActorComponent*> ActorComponents = Owner->GetComponentsByTag(USkeletalMeshComponent::StaticClass(),FName("ragdoll"));
	UE_LOG(LogTemp, Warning, TEXT("URagdollComponent::SetLeaderPoseComponent %d"), ActorComponents.Num());
	if (ActorComponents.Num() == 0) return;
	
	for (auto ActorComponent : ActorComponents)
	{
		if (ActorComponent)
		{
			USkeletalMeshComponent* BufferSkeletalMeshComponent = Cast<USkeletalMeshComponent>(ActorComponent);
			if (BufferSkeletalMeshComponent)
			{
				UAnimInstance* BufferAnimInstance = BufferSkeletalMeshComponent->GetAnimInstance();
				if (AnimInstance)
				{
					AnimInstances.Add(BufferAnimInstance);	
				}
			}
		}
	}
}

void UAnimationComponent::PlayBase(EAnimationType Animation)
{
	if (AnimInstance && Animation != EAnimationType::NONE && Animations.Contains(Animation))
	{
		Play(Animations[Animation]);
	}
}

void UAnimationComponent::Play(UAnimMontage* AnimMontage)
{
	if (!AnimMontage) return;
	
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(AnimMontage);
	}

	if (!AnimInstances.Num() == 0)
	{
		for (auto BufferAnimInstance : AnimInstances)
		{
			BufferAnimInstance->Montage_Play(AnimMontage);
		}
	}
}

void UAnimationComponent::PlayStandBy(EStandByAnimationType StandByAnimation)
{
	if (StandByAnimation == EStandByAnimationType::NONE) return;
	if (!StandByAnimations.Contains(StandByAnimation)) return;

	Play(StandByAnimations[StandByAnimation]);
}

void UAnimationComponent::PlaySword(ESwordAnimationType StandByAnimation)
{
	if (StandByAnimation == ESwordAnimationType::NONE) return;
	if (!SwordAnimations.Contains(StandByAnimation)) return;

	Play(SwordAnimations[StandByAnimation]);
}

void UAnimationComponent::PlayLanding(ELandingAnimationType AnimationLanding)
{
	if (AnimationLanding == ELandingAnimationType::NONE) return;
	if (!LandingAnimations.Contains(AnimationLanding)) return;

	Play(LandingAnimations[AnimationLanding]);
}

void UAnimationComponent::Stop(float Blend)
{
	if (AnimInstance)
	{
		UAnimMontage* ActiveMontage =  AnimInstance->GetCurrentActiveMontage();
		if (ActiveMontage)
		{
			AnimInstance->Montage_Stop(Blend, ActiveMontage);
		}
	}
}



