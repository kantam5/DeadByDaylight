// Fill out your copyright notice in the Description page of Project Settings.


#include "Hook.h"
#include "Survivor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "SurvivorStatComponent.h"

AHook::AHook()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

	SurvivorHookedLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Survivor Hooked Location"));
	SurvivorHookedLocation->SetupAttachment(RootComponent);

	InteractCharacterLocation_0 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 0"));
	InteractCharacterLocations.Add(InteractCharacterLocation_0);
	InteractCharacterLocation_0->SetupAttachment(RootComponent);

	SaveProgress = 0.0f;
	MaxSaveProgress = 2.0f;

	HangProgress = 0.0f;
	MaxHangProgress = 1.5f;

	bHanging = false;
}

void AHook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHook::Interact()
{
	if (SaveProgress < MaxSaveProgress && bHanging == true)
	{
		Super::Interact();
		SaveProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (bHanging != false)
	{
		SaveProgress = 0.0f;
		bHanging = false;

		// 걸려있는 생존자 떨어뜨리기
		HangingSurvivor->SetActorEnableCollision(true);
		HangingSurvivor->GetCharacterMovement()->GravityScale = 1.0f;
		HangingSurvivor->SetHanged(false);
		HangingSurvivor = nullptr;
	}
}

void AHook::EndInteract()
{
	SaveProgress = 0.0f;
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
