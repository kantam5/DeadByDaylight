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
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	virtual void KillerInteract() override;
	virtual void KillerEndInteract() override;

	bool IsUsed() { return bUsed; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* KillerStunCollision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float BrokenProgress;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float MaxBrokenProgress;

	bool bUsed;
};
