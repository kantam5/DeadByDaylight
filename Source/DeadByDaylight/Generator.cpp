// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Survivor.h"
#include "Misc/App.h"
#include "DBDGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGenerator::AGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;*/

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(RootComponent);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

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
