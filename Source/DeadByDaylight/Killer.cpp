// Fill out your copyright notice in the Description page of Project Settings.


#include "Killer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"
#include "KillerAnimInstance.h"
#include "InteractiveActor.h"
#include "Generator.h"
#include "Pallet.h"
#include "Window.h"
#include "Components/CapsuleComponent.h"
#include "Survivor.h"
#include "Hook.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/App.h"

AKiller::AKiller()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;

	WalkSpeed = 1400.0f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	HoldingAttack = 0.0f;
}

void AKiller::BeginPlay()
{
	Super::BeginPlay();
	
	// 생성자에서 호출 시 Head에 달리지 않음
	Camera->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "Head");
	
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

void AKiller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInteracting == true || bActionInteracting == true)
	{
		GetController()->SetIgnoreLookInput(true);
		GetController()->SetIgnoreMoveInput(true);
	}
	else if (bInteracting == false && bActionInteracting == false)
	{
		GetController()->ResetIgnoreInputFlags();
	}
}

void AKiller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AKiller::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AKiller::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("Attack", this, &AKiller::AttackAxis);
	// PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &AKiller::Attack);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &AKiller::EndAttack);
	// PlayerInputComponent->BindAction("LungeAttack", EInputEvent::IE_Repeat, this, &AKiller::LungeAttack);

	PlayerInputComponent->BindAxis("Killer Interact", this, &AKiller::Interact);
	PlayerInputComponent->BindAction("Killer Interact", EInputEvent::IE_Released, this, &AKiller::EndInteract);

	PlayerInputComponent->BindAction("Vault", EInputEvent::IE_Pressed, this, &AKiller::ActionInteract);
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

void AKiller::AttackAxis(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		if (HoldingAttack < 0.4f)
		{
			HoldingAttack += FApp::GetDeltaTime() * 1.0f;
		}
		else if (bHoldingAttack != true)
		{
			bHoldingAttack = true;
			LungeAttack();
		}
	}
}

void AKiller::Attack()
{
	if (bAttacking == true)
	{
		return;
	}

	bHoldingAttack = true;

	FLatentActionInfo Info;
	Info.CallbackTarget = this;
	Info.ExecutionFunction = FName("LungeAttack");
	Info.Linkage = 0;
	UKismetSystemLibrary::RetriggerableDelay(this, 1.0f, Info);

	if (!bHoldingAttack)
	{
		KillerAnimInstance->PlayAttackMontage();
	}

	bAttacking = true;
}

void AKiller::LungeAttack()
{
	GetCharacterMovement()->MaxWalkSpeed = 3000.0f;

	// 아니면 누르는 순간 속도를 늘려주고 
	// FVector LaunchVector = GetActorForwardVector() * 5000.0f;
	// LaunchCharacter(LaunchVector, false, false);

	FTimerHandle AttackTimerHandle;
	float MontageDelay = KillerAnimInstance->PlayAttackMontage() - 0.2f;
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AKiller::EndAttackMontage, MontageDelay);
}

void AKiller::EndAttack()
{
	if (HoldingAttack < 0.4f)
	{
		FTimerHandle AttackTimerHandle;
		float MontageDelay = KillerAnimInstance->PlayAttackMontage() - 0.2f;
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AKiller::EndAttackMontage, MontageDelay);
	}

	bHoldingAttack = false;
	HoldingAttack = 0.0f;
}

void AKiller::EndAttackMontage()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	// hit result에 따라 애니메이션 호출
	FTimerHandle AttackDelayTimerHandle;
	float AttackDelay = 1.0f;
	GetWorld()->GetTimerManager().SetTimer(AttackDelayTimerHandle, this, &AKiller::EndAttackDelay, AttackDelay);
}

void AKiller::EndAttackDelay()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
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
				bInteracting = true;
				SetActorLocation(FVector(InteractLocation->GetComponentLocation().X, InteractLocation->GetComponentLocation().Y, GetActorLocation().Z));

				FVector ToTarget = InteractingActor->GetActorLocation() - GetActorLocation();
				FRotator LookAtRotation = FRotator(ToTarget.Rotation());

				GetController()->SetControlRotation(LookAtRotation);

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
				FRotator LookAtRotation = FRotator(ToTarget.Rotation());

				GetController()->SetControlRotation(LookAtRotation);

				bInteracting = true;
			}
		}
		// Hook
		// overlapping에서 survivor는 제외해야함
		else if (MinOverlappingActor && MinOverlappingActor->IsA(AHook::StaticClass()) && bCarrying && Survivor)
		{
			AHook* Hook = Cast<AHook>(MinOverlappingActor);
			if (Hook && !Hook->IsHanging())
			{
				Hook->SetHangingSurvivor(Survivor);
				Hook->KillerInteract();
			}

			// Interact시 위치를 고정
			USceneComponent* InteractLocation = nullptr;
			float MinInteractDistance = 1000.0f;
			if (!InteractLocation)
			{
				for (USceneComponent* InteractCharacterLocation : Hook->InteractCharacterLocations)
				{
					float LocationDistance = FVector::Dist(GetActorLocation(), InteractCharacterLocation->GetComponentLocation());
					if (MinInteractDistance >= LocationDistance)
					{
						MinInteractDistance = LocationDistance;
						InteractLocation = InteractCharacterLocation;
					}
				}
			}

			SetActorLocation(FVector(InteractLocation->GetComponentLocation().X, InteractLocation->GetComponentLocation().Y, GetActorLocation().Z));

			FVector ToTarget = Hook->GetActorLocation() - GetActorLocation();
			FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);

			GetController()->SetControlRotation(LookAtRotation);

			bInteracting = true;
			// hook 애니메이션
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

void AKiller::ActionInteract()
{
	GetOverlappingActors(OverlappingActors);

	// 가장 가까운 InteractingActor
	AActor* MinOverlappingActor = nullptr;
	float MinDistance = 5000.0f;

	for (AActor* OverlappingActor : OverlappingActors)
	{
		float ActorDistance = FVector::Dist(GetActorLocation(), OverlappingActor->GetActorLocation());
		if (MinDistance > ActorDistance)
		{
			MinDistance = ActorDistance;
			MinOverlappingActor = OverlappingActor;
		}
	}

	bool bHook = false;
	if (MinOverlappingActor)
	{
		if (MinOverlappingActor->IsA(AHook::StaticClass()))
		{
			bHook = true;
		}
	}

	if (Controller != nullptr && Survivor && Survivor->IsCarried() && !bHook)
	{
		Survivor->SetActorEnableCollision(true);
		Survivor->SetCarried(false);
		Survivor->GetCharacterMovement()->GravityScale = 1.0f;
		Survivor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		Survivor = nullptr;
		bCarrying = false;
	}
	else if (Controller != nullptr && Survivor == nullptr)
	{
		// window
		if (MinOverlappingActor && MinOverlappingActor->IsA(AWindow::StaticClass()))
		{
			AWindow* Window = Cast<AWindow>(MinOverlappingActor);
			if (Window)
			{
				USceneComponent* MoveLocation = nullptr;
				USceneComponent* InteractLocation = nullptr;
				float MaxInteractDistance = 0.0f;
				float MinInteractDistance = 1000.0f;
				for (USceneComponent* InteractCharacterLocation : Window->InteractCharacterLocations)
				{
					float LocationDistance = FVector::Dist(GetActorLocation(), InteractCharacterLocation->GetComponentLocation());
					if (MaxInteractDistance <= LocationDistance)
					{
						MaxInteractDistance = LocationDistance;
						MoveLocation = InteractCharacterLocation;
					}
					if (MinInteractDistance >= LocationDistance)
					{
						MinInteractDistance = LocationDistance;
						InteractLocation = InteractCharacterLocation;
					}
				}

				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
				GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				SetActorLocation(FVector(InteractLocation->GetComponentLocation().X, InteractLocation->GetComponentLocation().Y, GetActorLocation().Z));

				FVector ToTarget = MoveLocation->GetComponentLocation() - InteractLocation->GetComponentLocation();
				FRotator LookAtRotation = FRotator(ToTarget.Rotation());
				GetController()->SetControlRotation(LookAtRotation);

				bActionInteracting = true;
				GetCharacterMovement()->StopMovementImmediately();

				FTimerHandle VaultTimerHandle;
				float MontageDelay = KillerAnimInstance->PlayVaultMontage();
				WindowPalletInteractMoveLocation = FVector(MoveLocation->GetComponentLocation().X, MoveLocation->GetComponentLocation().Y, GetActorLocation().Z);
				GetWorld()->GetTimerManager().SetTimer(VaultTimerHandle, this, &AKiller::EndVaultMontage, MontageDelay);
			}
		}
		// lift survivor
		else if (MinOverlappingActor && MinOverlappingActor->IsA(ASurvivor::StaticClass()))
		{
			Survivor = Cast<ASurvivor>(MinOverlappingActor);
			if (Survivor->GetHp() == 1 && !Survivor->IsCarried())
			{	
				FVector ToTarget = Survivor->GetActorLocation() - GetActorLocation();
				FRotator LookAtRotation = FRotator(ToTarget.Rotation());
				GetController()->SetControlRotation(LookAtRotation);

				bActionInteracting = true;
				GetCharacterMovement()->StopMovementImmediately();

				// carry 애니메이션
				bCarrying = true;
				FTimerHandle VaultTimerHandle;
				float MontageDelay = KillerAnimInstance->PlayLiftMontage();

				GetWorld()->GetTimerManager().SetTimer(VaultTimerHandle, this, &AKiller::EndLiftMontage, MontageDelay);
			}
		}
	}
}

void AKiller::EndVaultMontage()
{
	SetActorLocation(WindowPalletInteractMoveLocation);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	bActionInteracting = false;

	WindowPalletInteractMoveLocation = GetActorLocation();
}

void AKiller::EndLiftMontage()
{
	Survivor->SetActorEnableCollision(false);

	bActionInteracting = false;
	FDamageEvent DamageEvent;
	Survivor->TakeDamage(2.0f, DamageEvent, GetController(), this);
	Survivor->SetCarried(true);
	// survivor의 tick에서 처리하나?
	Survivor->GetCharacterMovement()->GravityScale = 0.0f;
	Survivor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("SurvivorHangLocation"));
}
