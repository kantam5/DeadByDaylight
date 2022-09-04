// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DBDGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEADBYDAYLIGHT_API ADBDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetHookRenderCustomDepth(bool state);
	
	void RepairCompleted();

	void ActivateExitGenerator();

	void GameOver(bool bWonGame);

private:
	int RemainGenerator;

	TArray<AActor*> ExitDoorSpawnPoints;

	int ExitDoorSpawnPointIndex_1;
	int ExitDoorSpawnPointIndex_2;

	UPROPERTY(EditDefaultsOnly, Category = "GamePlay")
	TSubclassOf<class AExitDoor> ExitDoorClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SurviveWidget;

	UUserWidget* SurviveScreen;
};
