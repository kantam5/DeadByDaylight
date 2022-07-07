// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Survivor.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AGenerator::AGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(RootComponent);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

	RepairProgress = 0.0f;
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AGenerator::HandleOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AGenerator::HandleEndOverlap);
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGenerator::Interact()
{
	Super::Interact();

	RepairProgress += 1.0f;
}

void AGenerator::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASurvivor* Survivor = Cast<ASurvivor>(OtherActor);
	RepairProgressScreen = CreateWidget<UUserWidget>(GetWorld(), RepairProgressWidget);
	if (RepairProgressScreen)
	{
		RepairProgressScreen->AddToViewport();
	}

}

void AGenerator::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (RepairProgressScreen)
	{
		RepairProgressScreen->RemoveFromViewport();
	}
}
