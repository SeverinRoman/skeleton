#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HurtBoxComponent.generated.h"


class UShapeComponent;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UHurtBoxComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHurtBoxComponent();

private:
	UPROPERTY(EditDefaultsOnly)
	FName TagHurtBox = "hurtbox";

	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY()
	AActor* Owner;

	UPROPERTY(VisibleInstanceOnly)
	TArray<UShapeComponent*> HurtBoxes;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void AddHurtBoxes();
	
	UFUNCTION()
	void ChangeVisibility(bool IsVisible);

private:
	virtual void BeginPlay() override;
};
