#include "SkeletonCharacter.h"

#include "GameInputComponent.h"


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
	GameInputComponent = FindComponentByClass<UGameInputComponent>();

	if (GameInputComponent)
	{
		GameInputComponent->SetupPlayerInputComponent(InputComponent);
	}
}

