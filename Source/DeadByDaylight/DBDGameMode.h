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

	void RepairCompleted();

	void ActivateExitGenerator();

private:
	int RemainGenerator;
};
