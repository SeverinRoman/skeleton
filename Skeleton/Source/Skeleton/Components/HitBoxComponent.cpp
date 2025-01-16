#include "HitBoxComponent.h"

#include "WeaponRightType.h"


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

void UHitBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHitBoxComponent::ToggleHitBox(EWeaponRightType WeaponRightType)
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
	// FQuat Rotation = FQuat::Identity;

	float Radius = HitBoxConfigs[WeaponRightType].Radius;
	float HalfHeight = HitBoxConfigs[WeaponRightType].HalfHeight;
	
	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(Radius, HalfHeight);
	CollisionShape.Capsule.Radius = Radius;
	CollisionShape.Capsule.HalfHeight = HalfHeight;
	
	World->SweepSingleByProfile(OutHit, Start, End, Rotation, CollisionProfileName.Name, CollisionShape);
	
	if (IsDebug)
	{
		DrawDebugCapsule(World, Start, HalfHeight, Radius, Rotation, FColor::Green, false, 0.1f);
		// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("My Location is: %s"), ( OutHit.IsValidBlockingHit() ? TEXT("true") : TEXT("false") )));
	}
	
}



