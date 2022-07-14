// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitDoor.h"
#include "Components/SphereComponent.h"
#include "Misc/App.h"

AExitDoor::AExitDoor()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

	PowerProgress = 0.0f;
	MaxPowerProgress = 2.0f;

	bPowered = false;

}

void AExitDoor::Interact()
{
	if (PowerProgress < MaxPowerProgress)
	{
		Super::Interact();
	
		PowerProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (bPowered != true)
	{
		bPowered = true;
	
		// ¹®¿­±â
		SetActorHiddenInGame(true);
	}
}