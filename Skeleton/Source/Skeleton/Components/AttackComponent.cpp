#include "AttackComponent.h"

#include "WeaponComponent.h"
#include "AnimationComponent.h"
#include "SwordAnimationType.h"
#include "StateComponent.h"


UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UAttackComponent::Init()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	WeaponComponent = Owner->FindComponentByClass<UWeaponComponent>();
	AnimationComponent = Owner->FindComponentByClass<UAnimationComponent>();
	StateComponent = Owner->FindComponentByClass<UStateComponent>();

	UpdateWeapon();
}

void UAttackComponent::UpdateWeapon()
{
	if (!WeaponComponent) return;

	WeaponRight = WeaponComponent->GetWeaponHandRight();
	WeaponLeft = WeaponComponent->GetWeaponHandLeft();
}

void UAttackComponent::RightWeak()
{
	if (!AnimationComponent || !StateComponent) return;

	EStateType State = StateComponent->GetState();
	if (State != EStateType::IDLE && State != EStateType::MOVE) return;
	StateComponent->SetState(EStateType::ATTACK);
	
	UpdateWeapon();
	switch (WeaponRight) {
	case EWeaponRightType::FIST:
		break;
	case EWeaponRightType::SWORD:

		switch (Combo)
		{
		case 0:
			AnimationComponent->PlaySword(ESwordAnimationType::SWORD_WEAK_ATTACK_0);
			break;
		case 1:
			AnimationComponent->PlaySword(ESwordAnimationType::SWORD_WEAK_ATTACK_1);
			break;
		case 2:
			AnimationComponent->PlaySword(ESwordAnimationType::SWORD_WEAK_ATTACK_2);
			break;
		}
		
		break;
	}
}

void UAttackComponent::RightStrong()
{
	UpdateWeapon();

	switch (WeaponRight) {
	case EWeaponRightType::FIST:
		break;
	case EWeaponRightType::SWORD:
		break;
	}
}

void UAttackComponent::LeftWeak()
{
	UpdateWeapon();
}

void UAttackComponent::LeftStrong()
{
	UpdateWeapon();
}

void UAttackComponent::AttackEnd()
{
	if (StateComponent)
	{
		StateComponent->SetState(EStateType::IDLE);
	}
}



