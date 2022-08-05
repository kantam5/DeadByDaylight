// Fill out your copyright notice in the Description page of Project Settings.


#include "Window.h"
#include "Components/BoxComponent.h"

AWindow::AWindow()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(RootComponent);
}
