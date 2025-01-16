#include "MoveComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

#include "StateComponent.h"
#include "AnimationComponent.h"
#include "StaminaComponent.h"
#include "Chaos/BoundingVolumeUtilities.h"


UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMoveComponent::Init()
{
	Owner = GetOwner();
	if (!Owner) return;

	Character = Cast<ACharacter>(Owner);
	
	CharacterMovementComponent = Owner->GetComponentByClass<UCharacterMovementComponent>();
	StateComponent = Owner->GetComponentByClass<UStateComponent>();
	StaminaComponent = Owner->GetComponentByClass<UStaminaComponent>();
	AnimationComponent = Owner->GetComponentByClass<UAnimationComponent>();

	if (StaminaComponent)
	{
		StaminaComponent->OnStaminaEnd.AddDynamic(this, &UMoveComponent::OnStaminaEnd);
	}

	switch (StartMove) {
	case EMoveType::NONE:
		break;
	case EMoveType::WALK:
		Walk();
		break;
	case EMoveType::RUN:
		Run();
		break;
	case EMoveType::SPRINT:
		Sprint();
		break;
	}

	if (CharacterMovementComponent)
	{
		SaveRotationRate = CharacterMovementComponent->RotationRate;
	}
}

void UMoveComponent::Sprint()
{
	if(CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed = SprintSpeed;
	}

	CurrentMove = EMoveType::SPRINT;
}

void UMoveComponent::Run()
{
	if(CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed = RunSpeed;
	}

	CurrentMove = EMoveType::RUN;
}

void UMoveComponent::Walk()
{
	if(CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed = WalkSpeed;
	}
	
	CurrentMove = EMoveType::WALK;
}

void UMoveComponent::ToggleRotation(bool bIsRotation)
{
	if (bIsRotation == IsEnableRotation) return;

	if (bIsRotation)
	{
		CharacterMovementComponent->RotationRate = SaveRotationRate;
	}
	else
	{
		CharacterMovementComponent->RotationRate = FRotator::ZeroRotator;
	}
	
	IsEnableRotation = bIsRotation;
}

void UMoveComponent::Move(float X, float Y)
{
	if (Character)
	{
		FRotator RotatorX = Character->GetControlRotation();
		RotatorX.Pitch = 0.f;
		RotatorX.Roll = 0.f;
		
		FVector DirectionX = UKismetMathLibrary::GetForwardVector(RotatorX);

		
		FRotator RotatorY = Character->GetControlRotation();
		RotatorY.Pitch = 0.f;
		
		FVector DirectionY = UKismetMathLibrary::GetRightVector(RotatorY);


		Character->AddMovementInput(DirectionX, X);
		Character->AddMovementInput(DirectionY, Y);
	}


	StopAnimation();
	StopStandBy();
}

void UMoveComponent::StopStandBy()
{
	if (!AnimationComponent || !StateComponent) return;

	if (StateComponent->GetState() == EStateType::STANDBY)
	{
		AnimationComponent->Stop();
		StateComponent->SetState(EStateType::MOVE);
	}
}

void UMoveComponent::StopAnimation()
{
	if (!AnimationComponent || !StateComponent) return;

	EStateType State = StateComponent->GetState();
	if (State == EStateType::IDLE)
	{
		AnimationComponent->Stop();
	}
}

void UMoveComponent::OnStaminaEnd()
{
	Run();
}
