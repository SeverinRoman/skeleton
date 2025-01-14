#include "InputManagerComponent.h"

#include "InputCatcherComponent.h"
#include "MoveComponent.h"
#include "DodgeComponent.h"
#include "JumpComponent.h"
#include "AttackComponent.h"

#include "GameFramework/Character.h"


UInputManagerComponent::UInputManagerComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}

void UInputManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UInputManagerComponent::Init()
{
	Owner = GetOwner();
	if (!Owner) return;

	World = GetWorld();

	Character = Cast<ACharacter>(Owner);

	InputCatcherComponent = Owner->GetComponentByClass<UInputCatcherComponent>();
	MoveComponent = Owner->GetComponentByClass<UMoveComponent>();
	DodgeComponent = Owner->GetComponentByClass<UDodgeComponent>();
	JumpComponent = Owner->GetComponentByClass<UJumpComponent>();
	AttackComponent = Owner->GetComponentByClass<UAttackComponent>();


	if (InputCatcherComponent)
	{
		InputCatcherComponent->OnInputMove.AddDynamic(this, &UInputManagerComponent::OnInputMove);
		InputCatcherComponent->OnInputLook.AddDynamic(this, &UInputManagerComponent::OnInputLook);
		
		InputCatcherComponent->OnInputDodgeRunJump.AddDynamic(this, &UInputManagerComponent::OnInputDodgeRunJump);

		InputCatcherComponent->OnInputRightAttackWeak.AddDynamic(this, &UInputManagerComponent::OnInputRightAttackWeak);
		InputCatcherComponent->OnInputRightAttackStrong.AddDynamic(this, &UInputManagerComponent::OnInputRightAttackStrong);
	}
}

void UInputManagerComponent::OnInputMove(const FInputActionInstance InputActionInstance)
{
	float X = InputActionInstance.GetValue().Get<FVector2D>().X;
	float Y = InputActionInstance.GetValue().Get<FVector2D>().Y;
	
	if (MoveComponent)
	{
		MoveComponent->Move(X, Y);
	}
}

void UInputManagerComponent::OnInputLook(const FInputActionInstance InputActionInstance) 
{
	float X = InputActionInstance.GetValue().Get<FVector2D>().X;
	float Y = InputActionInstance.GetValue().Get<FVector2D>().Y;

	if (Character)
	{
		Character->AddControllerYawInput(X);
		Character->AddControllerPitchInput(Y);
	}
}

void UInputManagerComponent::OnInputDodgeRunJump(const FInputActionInstance InputActionInstance, const bool IsPressed) 
{
	if (!DodgeComponent || !MoveComponent || !JumpComponent || !World) return;
	
	if (IsPressed)
	{
		if (bJump)
		{
			bJump = false;
			IsSprint = true;
			
			World->GetTimerManager().ClearTimer(TimerHandleRun);
			World->GetTimerManager().ClearTimer(TimerHandleJump);
			
			JumpComponent->Try();
			MoveComponent->Sprint();
			return;
		}

		
		IsSprint = false;
		World->GetTimerManager().SetTimer(TimerHandleRun, [&]() { IsSprint = true; MoveComponent->Sprint(); }, DurationRun, false);
	}
	else
	{
		World->GetTimerManager().ClearTimer(TimerHandleRun);
		
		MoveComponent->Run();

		if (!IsSprint)
		{
			DodgeComponent->Dodge();
		}

		if (IsSprint)
		{
			bJump = true;
			World->GetTimerManager().SetTimer(TimerHandleJump, [&]() { bJump = false; }, DurationJump, false);
		}

		IsSprint = false;
	}
}

void UInputManagerComponent::OnInputRightAttackWeak(const FInputActionInstance InputActionInstance, const bool IsPressed) 
{
	if (IsPressed)
	{
		if (AttackComponent)
		{
			AttackComponent->RightWeak();
		}
	}
}

void UInputManagerComponent::OnInputRightAttackStrong(const FInputActionInstance InputActionInstance, const bool IsPressed) 
{
	if (IsPressed)
	{
		if (AttackComponent)
		{
			AttackComponent->RightStrong();
		}
	}
}

