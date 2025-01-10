#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameInputComponent.generated.h"


class UInputMappingContext;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UGameInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGameInputComponent();

public:
	UFUNCTION()
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

private:
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMapping;
	
	UPROPERTY(EditDefaultsOnly)
	int PlayerNum = 0;

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
