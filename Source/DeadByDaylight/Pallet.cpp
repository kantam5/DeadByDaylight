// Fill out your copyright notice in the Description page of Project Settings.


#include "Pallet.h"
#include "Components/BoxComponent.h"

APallet::APallet()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(RootComponent);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	bUsed = false;
}

void APallet::BeginPlay()
{
}

void APallet::Interact()
{
	Super::Interact();

	FRotator UsedPalletRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 45.0f);
	Mesh->SetRelativeRotation(UsedPalletRotation);
	
	bUsed = true;
}
