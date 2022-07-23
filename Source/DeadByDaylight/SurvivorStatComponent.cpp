// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorStatComponent.h"
#include "DBDGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USurvivorStatComponent::USurvivorStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	bWantsInitializeComponent = true;

	Hp = 3;
}


// Called when the game starts
void USurvivorStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetMaxHp(Hp);
}

void USurvivorStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
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
		}
	}
}

void USurvivorStatComponent::OnAttacked(float DamageAmount)
{
	Hp -= DamageAmount;
	if (Hp <= 0)
	{
		Hp = 0;
	}

	UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"), Hp);
}
