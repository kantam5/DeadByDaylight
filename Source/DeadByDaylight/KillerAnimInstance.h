// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KillerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEADBYDAYLIGHT_API UKillerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UKillerAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	void PlayAttackMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	bool bFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;
};