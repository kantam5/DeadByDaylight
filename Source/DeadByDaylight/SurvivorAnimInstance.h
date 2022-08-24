// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SurvivorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEADBYDAYLIGHT_API USurvivorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USurvivorAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	float PlayVaultMontage();

	float PlayPullDownMontage();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bFalling;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bRunning;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bCrouching;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bInjured;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bSeriousInjured;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bInteracting;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bCarried;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bHanged;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bTraped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* VaultMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* PullDownMontage;
};
