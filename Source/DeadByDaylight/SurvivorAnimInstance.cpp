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

		if (Character->GetHp() == 2)
		{
			bInjured = true;
		}
		else if (Character->GetHp() == 1)
		{
			bSeriousInjured = true;
		}
	}
}
