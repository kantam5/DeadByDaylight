// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor.h"

// Sets default values
AInteractiveActor::AInteractiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	InteractCharacterLocation_0 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 0"));
	InteractCharacterLocations.Add(InteractCharacterLocation_0);
	InteractCharacterLocation_0->SetupAttachment(RootComponent);

	InteractCharacterLocation_1 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 1"));
	InteractCharacterLocations.Add(InteractCharacterLocation_1);
	InteractCharacterLocation_1->SetupAttachment(RootComponent);

	InteractCharacterLocation_2 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 2"));
	InteractCharacterLocations.Add(InteractCharacterLocation_2);
	InteractCharacterLocation_2->SetupAttachment(RootComponent);

	InteractCharacterLocation_3 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 3"));
	InteractCharacterLocations.Add(InteractCharacterLocation_3);
	InteractCharacterLocation_3->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveActor::Interact()
{
	
}

void AInteractiveActor::EndInteract()
{

}

void AInteractiveActor::KillerInteract()
{

}

void AInteractiveActor::KillerEndInteract()
{

}

bool AInteractiveActor::IsBroken()
{
	return bBroken;
}
