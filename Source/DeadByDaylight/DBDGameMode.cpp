// Fill out your copyright notice in the Description page of Project Settings.


#include "DBDGameMode.h"
#include "ExitDoor.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Blueprint/UserWidget.h"

void ADBDGameMode::BeginPlay()
{
	Super::BeginPlay();

	RemainGenerator = 1;

	UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), ExitDoorSpawnPoints);

	ExitDoorSpawnPointIndex_1 = FMath::RandRange(0, 1);
	ExitDoorSpawnPointIndex_2 = FMath::RandRange(2, 3);
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
	FVector ExitDoorSpawnLocation_1 = ExitDoorSpawnPoints[ExitDoorSpawnPointIndex_1]->GetActorLocation();
	FRotator ExitDoorSpawnRotation_1 = ExitDoorSpawnPoints[ExitDoorSpawnPointIndex_1]->GetActorRotation();

	FVector ExitDoorSpawnLocation_2 = ExitDoorSpawnPoints[ExitDoorSpawnPointIndex_2]->GetActorLocation();
	FRotator ExitDoorSpawnRotation_2 = ExitDoorSpawnPoints[ExitDoorSpawnPointIndex_2]->GetActorRotation();

	GetWorld()->SpawnActor<AExitDoor>(ExitDoorClass, ExitDoorSpawnLocation_1, ExitDoorSpawnRotation_1);
	GetWorld()->SpawnActor<AExitDoor>(ExitDoorClass, ExitDoorSpawnLocation_2, ExitDoorSpawnRotation_2);
}

void ADBDGameMode::GameOver(bool)
{
	SurviveScreen = CreateWidget<UUserWidget>(GetWorld(), SurviveWidget);
	if (SurviveScreen)
	{
		SurviveScreen->AddToViewport();
	}
}
