#pragma once

#include "CoreMinimal.h"
#include "WeaponLeftType.h"
#include "WeaponRightType.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


enum class EWeaponRightType : uint8;
enum class EWeaponLeftType : uint8;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

public:
	UFUNCTION()
	EWeaponRightType GetWeaponHandRight() { return  CurrentWeaponHandRight; };

	UFUNCTION()
	EWeaponLeftType GetWeaponHandLeft() { return  CurrentWeaponHandLeft; };

	UFUNCTION()
	void SetWeaponHandRight(EWeaponRightType NewWeaponRightType);

	UFUNCTION()
	void SetWeaponHandLeft(EWeaponLeftType NewWeaponLeftType);
	
private:
	UPROPERTY(EditDefaultsOnly)
	EWeaponRightType StartWeaponHandRight = EWeaponRightType::FIST;

	UPROPERTY(EditDefaultsOnly)
	EWeaponLeftType StartWeaponHandLeft = EWeaponLeftType::FIST;
	
private:
	UPROPERTY()
	TMap<EWeaponRightType, UStaticMeshComponent* > RightHandWeapons;
	
	UPROPERTY()
	TMap<EWeaponLeftType, UStaticMeshComponent* > LeftHandWeapons;

private:
	UPROPERTY(VisibleInstanceOnly)
	EWeaponRightType CurrentWeaponHandRight;

	UPROPERTY(VisibleInstanceOnly)
	EWeaponLeftType CurrentWeaponHandLeft;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void ClearWeaponHandRight();

	UFUNCTION()
	void ClearWeaponHandLeft();

private:
	virtual void BeginPlay() override;
		
};
