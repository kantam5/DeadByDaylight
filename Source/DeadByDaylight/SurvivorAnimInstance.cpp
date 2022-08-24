// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Survivor.h"

USurvivorAnimInstance::USurvivorAnimInstance()
{
	bRunning = false;
	bInjured = false;
	bSeriousInjured = false;
	bInteracting = false;
	bCarried = false;
	bHanged = false;
	bTraped = false;
}

void USurvivorAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();

		ASurvivor* Character = Cast<ASurvivor>(Pawn);

		bFalling = Character->GetMovementComponent()->IsFalling();
		bCrouching = Character->GetMovementComponent()->IsCrouching();
		bRunning = Character->IsRunning();
		bInteracting = Character->IsInteracting();
		bCarried = Character->IsCarried();
		bHanged = Character->IsHanged();
		bTraped = Character->IsTraped();

		if (Character->GetHp() == 3)
		{
			bInjured = false;
			bSeriousInjured = false;
		}
		if (Character->GetHp() == 2)
		{
			bInjured = true;
			bSeriousInjured = false;
		}
		else if (Character->GetHp() == 1)
		{
			bInjured = true;
			bSeriousInjured = true;
		}
	}
}

float USurvivorAnimInstance::PlayVaultMontage()
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

float USurvivorAnimInstance::PlayPullDownMontage()
{
	if (!Montage_IsPlaying(PullDownMontage))
	{
		return Montage_Play(PullDownMontage);
	}
	else
	{
		return 0.0f;
	}
}
