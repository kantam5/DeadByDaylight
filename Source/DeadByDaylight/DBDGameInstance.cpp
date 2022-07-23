// Fill out your copyright notice in the Description page of Project Settings.


#include "DBDGameInstance.h"

UDBDGameInstance::UDBDGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> SurvivorDATA(TEXT("DataTable'/Game/Data/SurvivorTable.SurvivorTable'"));
	// 문제가 있으면 크래시
	if (SurvivorDATA.Succeeded())
	{
		SurvivorStats = SurvivorDATA.Object;
	}
}

void UDBDGameInstance::Init()
{
	Super::Init();
	
}

FSurvivorData* UDBDGameInstance::GetSurvivorData(int32 MaxHp)
{
	return SurvivorStats->FindRow<FSurvivorData>(*FString::FromInt(MaxHp), TEXT(""));
}
