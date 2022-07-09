// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Survivor.generated.h"


UCLASS()
class DEADBYDAYLIGHT_API ASurvivor : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RunSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bRunning;

public:
	ASurvivor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	bool IsRunning();

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void StartRun();
	void StopRun();

	void Interact(float Value);
	void Interact();

	TArray<AActor*> OverlappingActors;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


};
