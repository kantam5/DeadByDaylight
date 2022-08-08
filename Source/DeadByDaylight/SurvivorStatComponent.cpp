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

	MaxRepairProgress = 2.0f;
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

void USurvivorStatComponent::Recover()
{
	if (RecoverProgress < MaxRepairProgress && !bRecovered)
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
