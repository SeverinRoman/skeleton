#include "GameInputComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"


UGameInputComponent::UGameInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGameInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGameInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGameInputComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
}

