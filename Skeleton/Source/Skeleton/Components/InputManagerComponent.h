#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputManagerComponent.generated.h"


class UInputCatcherComponent;
class UMoveComponent;
class ACharacter;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UInputManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInputManagerComponent();

private:
	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY()
	AActor* Owner;
	
private:
	UPROPERTY()
	UInputCatcherComponent* InputCatcherComponent;
	
	UPROPERTY()
	UMoveComponent* MoveComponent;
	
	UPROPERTY()
	ACharacter* Character;

private:
	UFUNCTION()
	void Init();

private:
	UFUNCTION()
	void OnInputMove(FInputActionInstance InputActionInstance);

	UFUNCTION()
	void OnInputLook(FInputActionInstance InputActionInstance);

private:
	virtual void BeginPlay() override;
		
};
