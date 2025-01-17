#include "HitBoxComponent.h"

#include "WeaponRightType.h"
#include "Kismet/GameplayStatics.h"


UHitBoxComponent::UHitBoxComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHitBoxComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UHitBoxComponent::Init()
{
	Owner = GetOwner();
	World = GetWorld();
}

void UHitBoxComponent::BeginHitBox()
{
	HitActors.Empty();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("UHitBoxComponent::BeginHitBox"));
}

void UHitBoxComponent::TickHitBox(EWeaponRightType WeaponRightType)
{
	if (!World) return;
	if (!Owner) return;
	if (WeaponRightType == EWeaponRightType::NONE) return;
	if (!HitBoxConfigs.Contains(WeaponRightType)) return;

	UActorComponent* ActorComponent = Owner->FindComponentByTag(UStaticMeshComponent::StaticClass(), HitBoxConfigs[WeaponRightType].TagMesh);
	if (!ActorComponent) return;
	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(ActorComponent);
	if (!StaticMeshComponent) return;

	FHitResult OutHit;
	
	FVector Start = StaticMeshComponent->GetSocketLocation(HitBoxConfigs[WeaponRightType].SocketStart);
	FVector End = StaticMeshComponent->GetSocketLocation(HitBoxConfigs[WeaponRightType].SocketEnd);
	
	FQuat Rotation = StaticMeshComponent->GetSocketRotation(HitBoxConfigs[WeaponRightType].SocketStart).Quaternion();

	float Radius = HitBoxConfigs[WeaponRightType].Radius;
	float HalfHeight = HitBoxConfigs[WeaponRightType].HalfHeight;
	
	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(Radius, HalfHeight);
	
	World->SweepSingleByProfile(OutHit, Start, Start, Rotation, CollisionProfileName.Name, CollisionShape);
	
	if (IsDebug)
	{
		DrawDebugCapsule(World, Start, HalfHeight, Radius, Rotation, FColor::Green, false, 0.05f);// Таймаут 1 секунда для удобства наблюдения
	}

	AActor* HitActor = OutHit.GetActor();
	HitHitBox(HitActor, HitBoxConfigs[WeaponRightType]);
}

void UHitBoxComponent::HitHitBox(AActor* Actor, FHitBoxConfig HitBoxConfig)
{
	if (!Actor || !Owner) return;
	if (Actor == Owner) return;
	
	if (HitActors.Contains(Actor)) return;
	HitActors.Add(Actor);
	
	APawn* Pawn = Owner->GetInstigator();
	if (Pawn)
	{
		AController* Controller = Pawn->GetController();
		if (Controller)
		{
			UGameplayStatics::ApplyDamage(Actor, HitBoxConfig.Damage, Controller, Owner, HitBoxConfig.DamageTypeClass);

			if (IsDebug)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("UHitBoxComponent::HitHitBox: %s"), *Actor->GetName()));
			}
		}
	}
}





