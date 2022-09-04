// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Killer.generated.h"

UCLASS()
class DEADBYDAYLIGHT_API AKiller : public ACharacter
{
	GENERATED_BODY()

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
	void PickUpTrap();
	void EndPickUpTrapMontage();

	void SetKillerInteractLocation(AActor* MinOverlappingActor);
	void Interact(float Value);
	void EndInteract();

	void SetKillerActionInteractLocation(AActor* MinOverlappingActor);
	void ActionInteract();
	void EndVaultMontage();
	void EndLiftMontage();

	AActor* GetMinOverlappingActor();

public:
	void KnockOut();
	void EndKnockOut();

	void SetInteracting(bool state);
	bool IsInteracting() { return bInteracting; }

	void SetCarrying(bool state);
	bool IsCarrying() { return bCarrying; }

	void SetActionInteracting(bool state);
	bool IsActionInteracting() { return bActionInteracting; }

	void SetUsingPower(bool state);
	bool IsUsingPower() { return bUsingPower; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = light, meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* EyeLight;

	UPROPERTY()
	class UKillerAnimInstance* KillerAnimInstance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeapon> WeaponClass;
	UPROPERTY()
	AWeapon* Weapon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABearTrap> BearTrapClass;
	UPROPERTY()
	ABearTrap* BearTrap;

	bool bCanAttack;
	bool bHoldingAttack;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bAttackDelay;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float MaxHoldingAttackProgress;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float HoldingAttackProgress;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	int32 MaxPowerCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	int32 PowerCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float PowerProgress;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float MaxPowerProgress;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float AttackDelaySpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float CarryingWalkSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool bAttacking;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bInteracting;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bCarrying;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bActionInteracting;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bUsingPower;

	TArray<AActor*> OverlappingActors;
	class AInteractiveActor* InteractingActor;
	FVector WindowPalletInteractMoveLocation;

	class ASurvivor* Survivor;

	class ADBDGameMode* DBDGameMode;
};
