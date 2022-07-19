// Fill out your copyright notice in the Description page of Project Settings.


#include "KillerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UKillerAnimInstance::UKillerAnimInstance()
{

}

void UKillerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();

		ACharacter* Character = Cast<ACharacter>(Pawn);
		bFalling = Character->GetMovementComponent()->IsFalling();
	}
}

void UKillerAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}
