// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "DBDGameInstance.generated.h"

USTRUCT()
struct FSurvivorData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HangedCount;
};

/**
 * 
 */
UCLASS()
class DEADBYDAYLIGHT_API UDBDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UDBDGameInstance();

	virtual void Init() override;

	FSurvivorData* GetSurvivorData(int32 MaxHp);

private:
	UPROPERTY()
	class UDataTable* SurvivorStats;

};
