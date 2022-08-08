// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "Pallet.generated.h"

/**
 * 
 */
UCLASS()
class DEADBYDAYLIGHT_API APallet : public AInteractiveActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APallet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Interact() override;

	bool GetUsed() { return bUsed; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision;
	
	bool bUsed;
};
