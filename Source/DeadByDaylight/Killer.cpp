// Fill out your copyright notice in the Description page of Project Settings.


#include "Killer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"
#include "KillerAnimInstance.h"
#include "InteractiveActor.h"
#include "Generator.h"
#include "Pallet.h"

// Sets default values
AKiller::AKiller()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetMesh(), "Head");

	WalkSpeed = 1400.0f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called when the game starts or when spawned
void AKiller::BeginPlay()
{
	Super::BeginPlay();
	
	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	if (Weapon)
	{
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
		Weapon->SetOwner(this);
	}

}

void AKiller::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	KillerAnimInstance = Cast<UKillerAnimInstance>(GetMesh()->GetAnimInstance());
	if (KillerAnimInstance)
	{
		KillerAnimInstance->OnMontageEnded.AddDynamic(this, &AKiller::OnAttackMontageEnded);
		KillerAnimInstance->OnAttackHit.AddUObject(this, &AKiller::AttackCheck);
	}
}


// Called every frame
void AKiller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKiller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AKiller::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AKiller::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &AKiller::Attack);

	PlayerInputComponent->BindAxis("Killer Interact", this, &AKiller::Interact);
	PlayerInputComponent->BindAction("Killer Interact", EInputEvent::IE_Released, this, &AKiller::EndInteract);
}


void AKiller::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AKiller::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AKiller::Attack()
{
	if (bAttacking == true)
	{
		return;
	}

	KillerAnimInstance->PlayAttackMontage();

	bAttacking = true;
}

void AKiller::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bAttacking = false;
}

// 몽타주에서 설정한 AttackHit
void AKiller::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.0f;
	float AttackRadius = 50.0f;

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);
	UE_LOG(LogTemp, Warning, TEXT("Attack"));

	if (bResult && HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());

		FDamageEvent DamageEvent;
		HitResult.GetActor()->TakeDamage(1.0f, DamageEvent, GetController(), this);
	}
}

void AKiller::Interact(float Value)
{
	// Survivor와 Overlap된 Actor들 중에서 가장 가까운 Actors에 Interact
	GetOverlappingActors(OverlappingActors);

	if ((Controller != nullptr) && (Value != 0.0f) && !OverlappingActors.IsEmpty())
	{
		// 가장 가까운 InteractingActor
		AActor* MinOverlappingActor = nullptr;
		float MinDistance = 5000.0f;

		if (!OverlappingActors.IsEmpty())
		{
			for (AActor* OverlappingActor : OverlappingActors)
			{
				float ActorDistance = FVector::Dist(GetActorLocation(), OverlappingActor->GetActorLocation());
				if (MinDistance > ActorDistance)
				{
					MinDistance = ActorDistance;
					MinOverlappingActor = OverlappingActor;
				}
			}
		}

		if (MinOverlappingActor && MinOverlappingActor->IsA(AGenerator::StaticClass()))
		{
			InteractingActor = Cast<AGenerator>(MinOverlappingActor);
			if (InteractingActor && !InteractingActor->IsBroken())
			{
				InteractingActor->KillerInteract();
			}

			// Interact시 위치를 고정
			USceneComponent* InteractLocation = nullptr;
			float MinInteractDistance = 1000.0f;
			if (!InteractLocation)
			{
				for (USceneComponent* InteractCharacterLocation : InteractingActor->InteractCharacterLocations)
				{
					float LocationDistance = FVector::Dist(GetActorLocation(), InteractCharacterLocation->GetComponentLocation());
					if (MinInteractDistance >= LocationDistance)
					{
						MinInteractDistance = LocationDistance;
						InteractLocation = InteractCharacterLocation;
					}
				}
			}

			if (!InteractingActor->IsBroken())
			{
				SetActorLocation(FVector(InteractLocation->GetComponentLocation().X, InteractLocation->GetComponentLocation().Y, GetActorLocation().Z));

				FVector ToTarget = InteractingActor->GetActorLocation() - GetActorLocation();
				FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
				SetActorRotation(LookAtRotation);

				bInteracting = true;
			}
		}
		// Pallet
		else if (MinOverlappingActor && MinOverlappingActor->IsA(APallet::StaticClass()))
		{
			APallet* Pallet = Cast<APallet>(MinOverlappingActor);
			if (Pallet && !Pallet->IsBroken() && Pallet->IsUsed())
			{
				Pallet->KillerInteract();
			}

			// Interact시 위치를 고정
			USceneComponent* InteractLocation = nullptr;
			float MinInteractDistance = 1000.0f;
			if (!InteractLocation)
			{
				for (USceneComponent* InteractCharacterLocation : Pallet->InteractCharacterLocations)
				{
					float LocationDistance = FVector::Dist(GetActorLocation(), InteractCharacterLocation->GetComponentLocation());
					if (MinInteractDistance >= LocationDistance)
					{
						MinInteractDistance = LocationDistance;
						InteractLocation = InteractCharacterLocation;
					}
				}
			}

			if (Pallet->IsUsed())
			{
				SetActorLocation(FVector(InteractLocation->GetComponentLocation().X, InteractLocation->GetComponentLocation().Y, GetActorLocation().Z));

				FVector ToTarget = Pallet->GetActorLocation() - GetActorLocation();
				FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
				SetActorRotation(LookAtRotation);

				bInteracting = true;
			}
		}
	}
}

void AKiller::EndInteract()
{
	if (InteractingActor)
	{
		InteractingActor->KillerEndInteract();
		InteractingActor = nullptr;
	}

	bInteracting = false;
}
