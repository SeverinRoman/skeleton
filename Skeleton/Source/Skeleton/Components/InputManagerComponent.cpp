#include "InputManagerComponent.h"

#include "InputCatcherComponent.h"
#include "MoveComponent.h"
#include "DodgeComponent.h"
#include "JumpComponent.h"

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

	InputCatcherComponent = Owner->GetComponentByClass<UInputCatcherComponent>();
	MoveComponent = Owner->GetComponentByClass<UMoveComponent>();
	DodgeComponent = Owner->GetComponentByClass<UDodgeComponent>();
	JumpComponent = Owner->GetComponentByClass<UJumpComponent>();
	Character = Cast<ACharacter>(Owner);

	if (InputCatcherComponent)
	{
		InputCatcherComponent->OnInputMove.AddDynamic(this, &UInputManagerComponent::OnInputMove);
		InputCatcherComponent->OnInputLook.AddDynamic(this, &UInputManagerComponent::OnInputLook);
		
		InputCatcherComponent->OnInputDodgeRunJump.AddDynamic(this, &UInputManagerComponent::OnInputDodgeRunJump);

		InputCatcherComponent->OnInputAttackWeak.AddDynamic(this, &UInputManagerComponent::OnInputAttackWeak);
		InputCatcherComponent->OnInputAttackStrong.AddDynamic(this, &UInputManagerComponent::OnInputAttackStrong);
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

void UInputManagerComponent::OnInputAttackWeak(const FInputActionInstance InputActionInstance, const bool IsPressed) 
{
	
}

void UInputManagerComponent::OnInputAttackStrong(const FInputActionInstance InputActionInstance, const bool IsPressed) 
{
	
}

