#include "SkeletonCharacter.h"

#include "InputCatcherComponent.h"


ASkeletonCharacter::ASkeletonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASkeletonCharacter::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ASkeletonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkeletonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASkeletonCharacter::Init()
{
	InputCatcherComponent = FindComponentByClass<UInputCatcherComponent>();

	if (InputCatcherComponent)
	{
		InputCatcherComponent->SetupPlayerInputComponent(InputComponent);
	}
}

