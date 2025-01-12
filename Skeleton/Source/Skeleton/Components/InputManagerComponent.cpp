#include "InputManagerComponent.h"

#include "InputCatcherComponent.h"
#include "MoveComponent.h"

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

	InputCatcherComponent = Owner->GetComponentByClass<UInputCatcherComponent>();
	MoveComponent = Owner->GetComponentByClass<UMoveComponent>();
	Character = Cast<ACharacter>(Owner);

	if (InputCatcherComponent)
	{
		InputCatcherComponent->OnInputMove.AddDynamic(this, &UInputManagerComponent::OnInputMove);
		InputCatcherComponent->OnInputLook.AddDynamic(this, &UInputManagerComponent::OnInputLook);
	}
}

void UInputManagerComponent::OnInputMove(FInputActionInstance InputActionInstance)
{
	float X = InputActionInstance.GetValue().Get<FVector2D>().X;
	float Y = InputActionInstance.GetValue().Get<FVector2D>().Y;
	
	if (MoveComponent)
	{
		MoveComponent->Move(X, Y);
	}
}

void UInputManagerComponent::OnInputLook(FInputActionInstance InputActionInstance)
{
	float X = InputActionInstance.GetValue().Get<FVector2D>().X;
	float Y = InputActionInstance.GetValue().Get<FVector2D>().Y;

	if (Character)
	{
		Character->AddControllerYawInput(X);
		Character->AddControllerPitchInput(Y);
	}
}

