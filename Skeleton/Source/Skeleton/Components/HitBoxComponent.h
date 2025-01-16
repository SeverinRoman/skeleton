#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitBoxComponent.generated.h"


enum class EWeaponRightType : uint8;

USTRUCT()
struct FHitBoxConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName TagMesh = "sword";

	UPROPERTY(EditDefaultsOnly)
	FName SocketStart = "BladeStart";

	UPROPERTY(EditDefaultsOnly)
	FName SocketEnd = "BladeEnd";
	
	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly)
	FVector Offset = FVector::ZeroVector;
	
	UPROPERTY(EditDefaultsOnly)
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(EditDefaultsOnly)
	float Radius = 50.f;

	UPROPERTY(EditDefaultsOnly)
	float HalfHeight = 100.f;
	
};


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UHitBoxComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHitBoxComponent();

	UFUNCTION(BlueprintCallable)
	void ToggleHitBox(EWeaponRightType WeaponRightType);

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<EWeaponRightType, FHitBoxConfig> HitBoxConfigs;

	UPROPERTY(EditDefaultsOnly)
	FCollisionProfileName CollisionProfileName;

	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;

private:
	UFUNCTION()
	void Init();
	
private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
