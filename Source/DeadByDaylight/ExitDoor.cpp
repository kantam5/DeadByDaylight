// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitDoor.h"

AExitDoor::AExitDoor()
{
	PowerProgress = 0.0f;
	MaxPowerProgress = 2.0f;

	bActivated = false;
	bPowered = false;

}

void AExitDoor::Interact()
{
	if (bActivated)
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
}