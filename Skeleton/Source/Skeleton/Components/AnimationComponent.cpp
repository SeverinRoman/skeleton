#include "AnimationComponent.h"

#include "StandByAnimationType.h"


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

}

void UAnimationComponent::Play(UAnimMontage* AnimMontage)
{
	if (AnimInstance && AnimMontage)
	{
		AnimInstance->Montage_Play(AnimMontage);
	}
}

void UAnimationComponent::PlayStandBy(EStandByAnimationType StandByAnimation)
{
	if (StandByAnimation == EStandByAnimationType::NONE) return;
	if (!StandByAnimations.Contains(StandByAnimation)) return;

	Play(StandByAnimations[StandByAnimation]);
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



