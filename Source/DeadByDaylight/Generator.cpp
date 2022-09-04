// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Survivor.h"
#include "Killer.h"
#include "Misc/App.h"
#include "DBDGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGenerator::AGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

	InteractCharacterLocation_0 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 0"));
	InteractCharacterLocations.Add(InteractCharacterLocation_0);
	InteractCharacterLocation_0->SetupAttachment(RootComponent);

	InteractCharacterLocation_1 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 1"));
	InteractCharacterLocations.Add(InteractCharacterLocation_1);
	InteractCharacterLocation_1->SetupAttachment(RootComponent);

	InteractCharacterLocation_2 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 2"));
	InteractCharacterLocations.Add(InteractCharacterLocation_2);
	InteractCharacterLocation_2->SetupAttachment(RootComponent);

	InteractCharacterLocation_3 = CreateDefaultSubobject<USceneComponent>(TEXT("Interact Character Location 3"));
	InteractCharacterLocations.Add(InteractCharacterLocation_3);
	InteractCharacterLocation_3->SetupAttachment(RootComponent);

	RepairProgress = 4.0f;
	MaxRepairProgress = 5.0f;

	BrokenProgress = 0.0f;
	MaxBrokenProgress = 1.1f;

	bRepaired = false;
	bBroken = false;

}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();

	// GameMode는 BeginPlay에서 설정한다. (Crash 발생)
	DBDGameMode = Cast<ADBDGameMode>(UGameplayStatics::GetGameMode(this));

	// SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AGenerator::HandleOverlap);
	// SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AGenerator::HandleEndOverlap);

	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->IsA(AKiller::StaticClass()))
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bBroken == true)
	{
		if (RepairProgress > 0.0f)
		{
			RepairProgress -= DeltaTime * 0.3f;
		}
	}
}

void AGenerator::Interact()
{
	if (RepairProgress < MaxRepairProgress)
	{
		Super::Interact();

		bBroken = false;
		RepairProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (bRepaired != true)
	{
		bRepaired = true;
		DBDGameMode->RepairCompleted();
	}
}

void AGenerator::KillerInteract()
{
	if (BrokenProgress < MaxBrokenProgress && bBroken == false)
	{
		Super::KillerInteract();
		BrokenProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (bBroken != true)
	{
		BrokenProgress = 0.0f;
		bBroken = true;
	}
}

void AGenerator::KillerEndInteract()
{
	BrokenProgress = 0.0f;
}

//void AGenerator::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	ASurvivor* Survivor = Cast<ASurvivor>(OtherActor);
//	RepairProgressScreen = CreateWidget<UUserWidget>(GetWorld(), RepairProgressWidget);
//	if (RepairProgressScreen)
//	{
//		RepairProgressScreen->AddToViewport();
//	}
//
//}
//
//void AGenerator::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (RepairProgressScreen)
//	{
//		RepairProgressScreen->RemoveFromViewport();
//	}
//}
