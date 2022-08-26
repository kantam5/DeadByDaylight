// Fill out your copyright notice in the Description page of Project Settings.


#include "Window.h"
#include "Components/BoxComponent.h"

AWindow::AWindow()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(RootComponent);

	InteractCharacterLocation_0 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 0"));
	InteractCharacterLocations.Add(InteractCharacterLocation_0);
	InteractCharacterLocation_0->SetupAttachment(RootComponent);

	InteractCharacterLocation_1 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 1"));
	InteractCharacterLocations.Add(InteractCharacterLocation_1);
	InteractCharacterLocation_1->SetupAttachment(RootComponent);
}
