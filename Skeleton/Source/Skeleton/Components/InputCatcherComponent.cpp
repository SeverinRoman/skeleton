#include "InputCatcherComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"


UInputCatcherComponent::UInputCatcherComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInputCatcherComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInputCatcherComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	AActor* Owner = GetOwner();

	if (!Owner) return;

	ACharacter* Character = Cast<ACharacter>(Owner);

	if (!Character) return;
	
	APlayerController* PlayerControllerr = Cast<APlayerController>(Character->GetController());

	if (!PlayerControllerr) return;
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControllerr->GetLocalPlayer());
	
	if (!Subsystem) return;

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, PlayerNum);

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	BindInputs();
}

void UInputCatcherComponent::BindInputs()
{
	if (!EnhancedInputComponent) return;

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputMoveStarted);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UInputCatcherComponent::OnInputMoveTriggered);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputMoveCompleted);

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputLookStarted);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UInputCatcherComponent::OnInputLookTriggered);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputLookCompleted);

	EnhancedInputComponent->BindAction(DodgeRunJumpAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputDodgeRunJumpStarted);
	EnhancedInputComponent->BindAction(DodgeRunJumpAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputDodgeRunJumpCompleted);
	
	EnhancedInputComponent->BindAction(WeakAttackAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputAttackWeakStarted);
	EnhancedInputComponent->BindAction(WeakAttackAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputAttackWeakCompleted);

	EnhancedInputComponent->BindAction(StrongAttackAction, ETriggerEvent::Started, this, &UInputCatcherComponent::OnInputAttackStrongStarted);
	EnhancedInputComponent->BindAction(StrongAttackAction, ETriggerEvent::Completed, this, &UInputCatcherComponent::OnInputAttackStrongCompleted);
}

void UInputCatcherComponent::UnBindInputs()
{
	if (!EnhancedInputComponent) return;
	
	EnhancedInputComponent->ClearActionBindings();
}

