// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorStatComponent.h"
#include "DBDGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "TimerManager.h"
#include "Survivor.h"

// Sets default values for this component's properties
USurvivorStatComponent::USurvivorStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
	bWantsInitializeComponent = true;

	Hp = 3;

	MaxRecoverProgress = 2.0f;
	RecoverProgress = 0.0f;

	MaxHangingTime = 5.0f;
	HangingTime = 0.0f;

	BloodRate = 1.0f;
}


// Called when the game starts
void USurvivorStatComponent::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.Target = this;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());

	// ...
	SetMaxHp(Hp);

	GetWorld()->GetTimerManager().SetTimer(BloodTimerHandle, this, &USurvivorStatComponent::SpawnBloodDecalActor, BloodRate, true, BloodRate);
	GetWorld()->GetTimerManager().PauseTimer(BloodTimerHandle);
}

void USurvivorStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Survivor = Cast<ASurvivor>(GetOwner());
}

void USurvivorStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Survivor->IsHanged())
	{
		IncreaseHangingTime();
	}
}

void USurvivorStatComponent::SetMaxHp(int32 MaxHp)
{
	auto DBDGameInstance = Cast<UDBDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (DBDGameInstance)
	{		
		auto StatData = DBDGameInstance->GetSurvivorData(Hp);
		if (StatData)
		{
			Hp = StatData->MaxHp;
			WalkSpeed = StatData->WalkSpeed;
			RunSpeed = StatData->RunSpeed;
			CrawlSpeed = StatData->CrawlSpeed;
			HangedCount = StatData->HangedCount;
		}
	}
}

void USurvivorStatComponent::OnAttacked(float DamageAmount)
{
	GetWorld()->GetTimerManager().UnPauseTimer(BloodTimerHandle);

	Hp -= DamageAmount;
	if (Hp <= 1)
	{
		Hp = 1;
	}

	UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"), Hp);
}

void USurvivorStatComponent::OnTrapped()
{
	if (Hp > 2)
	{
		OnAttacked(1);
	}

	UE_LOG(LogTemp, Warning, TEXT("OnTrapped %d"), Hp);
}

void USurvivorStatComponent::Recover()
{
	if (RecoverProgress < MaxRecoverProgress && !bRecovered)
	{
		RecoverProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (Hp < 3)
	{
		Hp++;
		RecoverProgress = 0.0f;

		if (Hp == 3)
		{
			GetWorld()->GetTimerManager().PauseTimer(BloodTimerHandle);
		}

		ASurvivor* Owner = Cast<ASurvivor>(GetOwner());
		Owner->RecoverHp();
	}
}

void USurvivorStatComponent::IncreaseHangingTime()
{
	// 富府扁 贸府
	if (HangingTime < MaxHangingTime && HangedCount < 3)
	{
		HangingTime += FApp::GetDeltaTime() * 1.0f;
	}
	else if (HangedCount < 3)
	{
		IncreaseHangedCount();
		HangingTime = 0.0f;
	}
}

int32 USurvivorStatComponent::IncreaseHangedCount()
{
	HangedCount++;

	UE_LOG(LogTemp, Warning, TEXT("Hanged Count is %d"), HangedCount);

	if (HangedCount >= 3)
	{
		HangedCount = 3;
		Hp = 0;

		Survivor->Destroy();
		
		return HangedCount;
	}

	return HangedCount;
}

void USurvivorStatComponent::SpawnBloodDecalActor()
{
	FVector DecalSpawnLocation = FVector(Survivor->GetActorLocation().X, Survivor->GetActorLocation().Y, 0.0f);
	FRotator DecalSpawnRotation = FRotator(0.0f, 0.0f, Survivor->GetActorRotation().Yaw);
	BloodDecal = GetWorld()->SpawnActor<ADecalActor>(DecalSpawnLocation, DecalSpawnRotation);
	if (BloodDecal != nullptr)
	{
		BloodDecal->SetDecalMaterial(BloodDecalMaterial);
		BloodDecal->SetLifeSpan(3.5f);
		BloodDecal->GetDecal()->DecalSize = FVector(120.0f, 120.0f, 120.0f);
	}
}
