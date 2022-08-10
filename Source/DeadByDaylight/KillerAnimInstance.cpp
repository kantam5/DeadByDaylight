// Fill out your copyright notice in the Description page of Project Settings.


#include "KillerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Killer.h"

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

		AKiller* Character = Cast<AKiller>(Pawn);

		bFalling = Character->GetMovementComponent()->IsFalling();
		bInteracting = Character->IsInteracting();
	}
}

void UKillerAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}

float UKillerAnimInstance::PlayVaultMontage()
{
	if (!Montage_IsPlaying(VaultMontage))
	{
		return Montage_Play(VaultMontage);
	}
	else
	{
		return 0.0f;
	}
}

float UKillerAnimInstance::PlayLiftMontage()
{
	if (!Montage_IsPlaying(LiftMontage))
	{
		return Montage_Play(LiftMontage);
	}
	else
	{
		return 0.0f;
	}
}

// ��Ÿ�ֿ��� ������ AttackHit
void UKillerAnimInstance::AnimNotify_AttackHit()
{
	OnAttackHit.Broadcast();
}
