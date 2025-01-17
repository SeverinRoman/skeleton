#include "EnemyCharacter.h"

#include "HealthComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (HealthComponent)
	{
		HealthComponent->Sub(Damage);
	}
	
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemyCharacter::Init()
{
	HealthComponent = GetComponentByClass<UHealthComponent>();
}

