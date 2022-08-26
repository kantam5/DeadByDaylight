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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Exit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	USceneComponent* InteractCharacterLocation_0;

	class ADBDGameMode* DBDGameMode;

	float PowerProgress;
	float MaxPowerProgress;
	bool bPowered;

	UFUNCTION()
	void HandleExitOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
