// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Survivor.generated.h"


UCLASS()
class DEADBYDAYLIGHT_API ASurvivor : public ACharacter
{
	GENERATED_BODY()

public:
	ASurvivor();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;

	bool IsRunning();
	bool IsInteracting();

	void SetCarried(bool state) { bCarried = state; }
	bool IsCarried() { return bCarried; }

	void SetHanged(bool state); // { bHanged = state; }
	bool IsHanged() { return bHanged; }

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void StartRun();
	void StopRun();

	void CrouchStart();
	void CrouchEnd();

	void Interact(float Value);
	void EndInteract();

	void Vault();
	void EndVaultMontage();

	void PullDown();
	void EndPullDownMontage();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	class USurvivorStatComponent* GetStat() { return Stat; }

	int32 GetHp() { return Hp; }
	void RecoverHp() { Hp++; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// 다른 생존자를 힐 할 때 필요
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Hp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RunSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bRunning;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bInteracting;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bCarried;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bHanged;

	UPROPERTY(VisibleAnywhere)
	USurvivorStatComponent* Stat;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> OverlappingActors;

	class AInteractiveActor* InteractingActor;

	UPROPERTY()
	class USurvivorAnimInstance* SurvivorAnimInstance;

	FVector WindowPalletInteractMoveLocation;

};
