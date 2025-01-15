#include "FallComponent.h"

#include "StateComponent.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"

#include "GameFramework/Character.h"


UFallComponent::UFallComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}

void UFallComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UFallComponent::Init()
{
	Owner = GetOwner();
	if (!Owner) return;
	
	StateComponent = Owner->GetComponentByClass<UStateComponent>();
	AnimationComponent = Owner->GetComponentByClass<UAnimationComponent>();
	HealthComponent = Owner->GetComponentByClass<UHealthComponent>();

	Character = Cast<ACharacter>(Owner);

	if (Character)
	{
		Character->LandedDelegate.AddDynamic(this, &UFallComponent::OnLanded);
	}
}

void UFallComponent::OnLanded(const FHitResult& Hit)
{
	if (!StateComponent) return;
	StateComponent->SetState(EStateType::LANDING);
	
	float Speed = StateComponent->GetVelocity().Z;
	
	if (IsDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("UFallComponent::OnLanded"));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("My Location is: %f"), Speed));
	}

	FLandingConfig LandingConfig = FLandingConfig();

	for (auto Element : LandingConfigs)
	{
		if (Element.Speed >= Speed)
		{
			LandingConfig = Element;
		}
	}
	
	if (AnimationComponent)
	{
		AnimationComponent->PlayLanding(LandingConfig.AnimationLanding);
	}

	if (HealthComponent)
	{
		HealthComponent->Sub(LandingConfig.Damage);
	}
}

void UFallComponent::LandedEnd()
{
	if (StateComponent)
	{
		StateComponent->SetState(EStateType::IDLE);
	}
}
