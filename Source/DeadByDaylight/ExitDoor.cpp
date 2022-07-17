// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitDoor.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Misc/App.h"
#include "Kismet/GameplayStatics.h"
#include "DBDGameMode.h"

AExitDoor::AExitDoor()
{
	Exit = CreateDefaultSubobject<UBoxComponent>(TEXT("Exit"));
	Exit->SetBoxExtent(FVector(480.0f));
	Exit->SetupAttachment(RootComponent);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

	PowerProgress = 0.0f;
	MaxPowerProgress = 2.0f;

	bPowered = false;
}

void AExitDoor::Interact()
{
	if (PowerProgress < MaxPowerProgress)
	{
		Super::Interact();
	
		PowerProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (bPowered != true)
	{
		bPowered = true;
	
		// 문열기
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetHiddenInGame(true);
		// 여기서 게임모드를 가지고 있다면 싸이클?
	}
}

void AExitDoor::BeginPlay()
{
	Super::BeginPlay();

	DBDGameMode = Cast<ADBDGameMode>(UGameplayStatics::GetGameMode(this));

	Exit->OnComponentBeginOverlap.AddDynamic(this, &AExitDoor::HandleExitOverlap);
}

void AExitDoor::HandleExitOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DBDGameMode->GameOver(true);
	
	APlayerController* SurvivorController = Cast<APlayerController>(OtherActor->GetInstigatorController());
	OtherActor->DisableInput(SurvivorController);
}
