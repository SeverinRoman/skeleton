#include "SkeletonCharacter.h"


ASkeletonCharacter::ASkeletonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASkeletonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkeletonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkeletonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

