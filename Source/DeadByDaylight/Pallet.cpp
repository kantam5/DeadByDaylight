// Fill out your copyright notice in the Description page of Project Settings.


#include "Pallet.h"
#include "Components/BoxComponent.h"

APallet::APallet()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(RootComponent);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	BrokenProgress = 0.0f;
	MaxBrokenProgress = 1.1f;

	bUsed = false;
}

void APallet::BeginPlay()
{
	Super::BeginPlay();
}

void APallet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APallet::Interact()
{
	Super::Interact();

	FRotator UsedPalletRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 45.0f);
	Mesh->SetRelativeRotation(UsedPalletRotation);
	
	bUsed = true;
}


void APallet::KillerInteract()
{
	if (BrokenProgress < MaxBrokenProgress && bBroken == false)
	{
		Super::KillerInteract();
		BrokenProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (bBroken != true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Broke"));
		BrokenProgress = 0.0f;
		bBroken = true;
		Destroy();
	}
}

void APallet::KillerEndInteract()
{
	BrokenProgress = 0.0f;
}
