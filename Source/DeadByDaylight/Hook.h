// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "Hook.generated.h"

/**
 * 
 */
UCLASS()
class DEADBYDAYLIGHT_API AHook : public AInteractiveActor
{
	GENERATED_BODY()
	
public:
	AHook();

	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
	virtual void EndInteract() override;

	virtual void KillerInteract() override;
	virtual void KillerEndInteract() override;

	void SetHangingSurvivor(class ASurvivor* Survivor);

	bool IsHanging() { return bHanging; }

private:
	UPROPERTY(EditAnywhere, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SurvivorHookedLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float SaveProgress;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float MaxSaveProgress;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float HangProgress;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float MaxHangProgress;


	bool bHanging;

	class ASurvivor* HangingSurvivor;
};
