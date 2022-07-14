// Fill out your copyright notice in the Description page of Project Settings.


#include "DBDGameMode.h"

void ADBDGameMode::BeginPlay()
{
	Super::BeginPlay();

	RemainGenerator = 5;

	UE_LOG(LogTemp, Warning, TEXT("RemainGenerator : %d"), RemainGenerator);
}

void ADBDGameMode::RepairCompleted()
{
	RemainGenerator--;
	UE_LOG(LogTemp, Warning, TEXT("RemainGenerator : %d"), RemainGenerator);

	if (RemainGenerator == 0)
	{
		ActivateExitGenerator();
	}
}

void ADBDGameMode::ActivateExitGenerator()
{

}
