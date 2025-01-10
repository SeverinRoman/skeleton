#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkeletonCharacter.generated.h"


UCLASS()
class SKELETON_API ASkeletonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASkeletonCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
