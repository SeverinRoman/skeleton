#include "MoveComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

#include "StateComponent.h"
#include "AnimationComponent.h"


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
	AnimationComponent = Owner->GetComponentByClass<UAnimationComponent>();
}

void UMoveComponent::Run()
{
	if(CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed = RunSpeed;
	}
}

void UMoveComponent::Walk()
{
	if(CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed = WalkSpeed;
	}
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

	StopStandBy();
}

void UMoveComponent::Crouch()
{
	if(Character)
	{
		Character->Crouch();
	}
}

void UMoveComponent::UnCrouch()
{
	if(Character)
	{
		Character->UnCrouch();
	}
}

void UMoveComponent::Jump()
{
	if(Character)
	{
		Character->Jump();
	}
}

void UMoveComponent::UnJump()
{
	if(Character)
	{
		Character->StopJumping();
	}
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
