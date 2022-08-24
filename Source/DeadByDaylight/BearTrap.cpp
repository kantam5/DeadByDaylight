// Fill out your copyright notice in the Description page of Project Settings.


#include "BearTrap.h"
#include "Components/SphereComponent.h"
#include "Survivor.h"

// Sets default values
ABearTrap::ABearTrap()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	InnerSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Inner Sphere Collision"));
	InnerSphereCollision->SetupAttachment(RootComponent);
	InnerSphereCollision->SetSphereRadius(80.0f);

	OuterSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Outer Sphere Collision"));
	OuterSphereCollision->SetupAttachment(RootComponent);
	OuterSphereCollision->SetSphereRadius(150.0f);

	UnlockProgress = 0.0f;
	MaxUnlockProgress = 2.0f;
	bTraping = false;
	bUsed = false;
}

void ABearTrap::Interact()
{
	if (UnlockProgress < MaxUnlockProgress)
	{
		UnlockProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (bTraping == true)
	{
		UnlockProgress = 0.0f;

		int flag = FMath::RandRange(0, 1);
		
		if (flag == 0)
		{
			Unlock();
		}
		else if (flag == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Try again"));
		}
	}
	else if (bTraping == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trap Unlock"));
		UnlockProgress = 0.0f;
		
		bUsed = true;
	}
}

void ABearTrap::EndInteract()
{
	UnlockProgress = 0.0f;
}

void ABearTrap::Unlock()
{
	UE_LOG(LogTemp, Warning, TEXT("Trap Unlock"));
	bTraping = false;

	if (Survivor != nullptr)
	{
		Survivor->SetTraped(false);
		Survivor = nullptr;
	}
}

// Called when the game starts or when spawned
void ABearTrap::BeginPlay()
{
	Super::BeginPlay();
	
	InnerSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABearTrap::HandleOverlap);
}

void ABearTrap::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bUsed == false)
	{
		if (OtherActor->IsA(ASurvivor::StaticClass()))
		{
			Survivor = Cast<ASurvivor>(OtherActor);
			if (Survivor->GetHp() >= 2)
			{
				Survivor->SetTraped(true);

				bTraping = true;
				bUsed = true;

				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Trap"));
				UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetName());
			}
		}
	}
}
