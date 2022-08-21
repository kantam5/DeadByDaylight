// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorStatComponent.h"
#include "DBDGameInstance.h"
#include "Kismet/GameplayStatics.h"
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

}

void USurvivorStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void USurvivorStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Hp < 3)
	{
		bRecovered = false;
	}
	else if (Hp >= 3)
	{
		bRecovered = true;
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
			HangedCount = StatData->HangedCount;
		}
	}
}

void USurvivorStatComponent::OnAttacked(float DamageAmount)
{
	Hp -= DamageAmount;
	if (Hp <= 1)
	{
		Hp = 1;
	}

	UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"), Hp);
}

void USurvivorStatComponent::OnTrapped()
{
	Hp -= 1;
	if (Hp <= 2)
	{
		Hp = 2;
	}

	UE_LOG(LogTemp, Warning, TEXT("OnTrapped %d"), Hp);
}

void USurvivorStatComponent::Recover()
{
	if (RecoverProgress < MaxRecoverProgress && !bRecovered)
	{
		RecoverProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (bRecovered != true)
	{
		Hp++;
		RecoverProgress = 0.0f;

		ASurvivor* Owner = Cast<ASurvivor>(GetOwner());
		Owner->RecoverHp();
	}
}

void USurvivorStatComponent::IncreaseHangingTime()
{
	// 말리기 처리
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
	if (HangedCount >= 3)
	{
		HangedCount = 3;
		Hp = 0;
		// 생존자 삭제하고 return
		// ui도 실행
		return HangedCount;
	}

	return HangedCount;
}
