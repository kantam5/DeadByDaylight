// Fill out your copyright notice in the Description page of Project Settings.


#include "Hook.h"
#include "Survivor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"

AHook::AHook()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

	SurvivorHookedLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Survivor Hooked Location"));
	SurvivorHookedLocation->SetupAttachment(RootComponent);

	HangProgress = 4.0f;
	MaxHangProgress = 5.0f;

	bHanging = false;
}

void AHook::KillerInteract()
{
	if (HangProgress < MaxHangProgress && bHanging == false)
	{
		Super::KillerInteract();
		HangProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (bHanging != true)
	{
		HangProgress = 0.0f;
		bHanging = true;

		HangingSurvivor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		HangingSurvivor->SetActorEnableCollision(false);
		HangingSurvivor->GetCharacterMovement()->GravityScale = 0.0f;
		HangingSurvivor->SetActorLocation(SurvivorHookedLocation->GetComponentLocation());
		HangingSurvivor->SetActorRotation(SurvivorHookedLocation->GetComponentRotation());
		HangingSurvivor->SetHanged(true);
	}
}

void AHook::KillerEndInteract()
{
	HangingSurvivor = nullptr;
	HangProgress = 0.0f;
}

void AHook::SetHangingSurvivor(ASurvivor* Survivor)
{
	HangingSurvivor = Survivor;
}
