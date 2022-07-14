// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class DEADBYDAYLIGHT_API AExitDoor : public AInteractiveActor
{
	GENERATED_BODY()
	
public:
	AExitDoor();

	virtual void Interact() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;

	float PowerProgress;
	float MaxPowerProgress;

	bool bPowered;
};
