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

public:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void AttackCheck();

	void Interact(float Value);
	void EndInteract();

	bool IsInteracting() { return bInteracting; }

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* Weapon;

	UPROPERTY()
	class UKillerAnimInstance* KillerAnimInstance;

	UPROPERTY(VisibleAnywhere, Category = "Pawn")
	bool bAttacking = false;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bInteracting = false;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> OverlappingActors;

	class AInteractiveActor* InteractingActor;
};
