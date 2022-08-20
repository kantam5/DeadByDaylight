// Fill out your copyright notice in the Description page of Project Settings.


#include "Pallet.h"
#include "Components/BoxComponent.h"
#include "Killer.h"

APallet::APallet()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(RootComponent);

	KillerStunCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Killer Stun Collision"));
	KillerStunCollision->SetupAttachment(RootComponent);
	KillerStunCollision->SetBoxExtent(FVector(250.0f, 200.0f, 200.0f));

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	BrokenProgress = 0.0f;
	MaxBrokenProgress = 1.1f;

	bUsed = false;
}

void APallet::BeginPlay()
{
	Super::BeginPlay();
}

void APallet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APallet::Interact()
{
	Super::Interact();

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	FVector CollisionLocation = KillerStunCollision->GetComponentLocation();

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		CollisionLocation,
		CollisionLocation + FVector(0.0f, 0.0f, 0.001f),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeBox(KillerStunCollision->GetScaledBoxExtent()),
		Params
	);

	FColor DrawColor;
	if (bResult)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
		DrawColor = FColor::Green;
	}
	else
	{
		DrawColor = FColor::Red;
	}
	DrawDebugBox(GetWorld(), CollisionLocation, KillerStunCollision->GetScaledBoxExtent(), DrawColor, false, 20.0f);

	if (bResult && HitResult.GetActor())
	{
		if (HitResult.GetActor()->IsA(AKiller::StaticClass()))
		{
			AKiller* Killer = Cast<AKiller>(HitResult.GetActor());
			Killer->KnockOut();
		}
	}

	FRotator UsedPalletRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 45.0f);
	Mesh->SetRelativeRotation(UsedPalletRotation);

	bUsed = true;
}


void APallet::KillerInteract()
{
	if (BrokenProgress < MaxBrokenProgress && bBroken == false)
	{
		Super::KillerInteract();
		BrokenProgress += FApp::GetDeltaTime() * 1.0f;
	}
	else if (bBroken != true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Broke"));
		BrokenProgress = 0.0f;
		bBroken = true;
		Destroy();
	}
}

void APallet::KillerEndInteract()
{
	BrokenProgress = 0.0f;
}
