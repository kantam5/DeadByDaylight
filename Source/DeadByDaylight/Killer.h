// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Killer.generated.h"

UCLASS()
class DEADBYDAYLIGHT_API AKiller : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;


public:
	// Sets default values for this character's properties
	AKiller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void AttackAxis(float Value);

	void Attack();
	void LungeAttack();
	void EndAttack();
	void EndAttackMontage();
	void EndAttackDelay();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void AttackCheck();

	void Power(float Value);
	void EndPower();
	void PressPower();
	void EndPressPowerMontage();

	void Interact(float Value);
	void EndInteract();

	void ActionInteract();
	void EndVaultMontage();
	void EndLiftMontage();

public:
	void KnockOut();
	void EndKnockOut();

	bool IsInteracting() { return bInteracting; }
	bool IsUsingPower() { return bUsingPower; }

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeapon> WeaponClass;
	UPROPERTY()
	AWeapon* Weapon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABearTrap> BearTrapClass;
	UPROPERTY()
	ABearTrap* BearTrap;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	int32 MaxPowerCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	int32 PowerCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float PowerProgress;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float MaxPowerProgress;

	UPROPERTY()
	class UKillerAnimInstance* KillerAnimInstance;

	UPROPERTY(VisibleAnywhere, Category = "Pawn")
	bool bAttacking = false;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bInteracting = false;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bCarrying = false;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bActionInteracting = false;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bUsingPower = false;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> OverlappingActors;

	class AInteractiveActor* InteractingActor;

	FVector WindowPalletInteractMoveLocation;

	class ASurvivor* Survivor;

	bool bCanAttack;

	bool bHoldingAttack;

	float HoldingAttack;
};
