#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


enum class EWeaponType : uint8;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

private:
	UPROPERTY(EditDefaultsOnly)
	EWeaponType StartWeapon;

private:
	virtual void BeginPlay() override;
		
};
