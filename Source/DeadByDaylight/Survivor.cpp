// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Math/UnrealMathUtility.h"
#include "InteractiveActor.h"
#include "Window.h"
#include "Pallet.h"
#include "Hook.h"
#include "Generator.h"
#include "ExitDoor.h"
#include "BearTrap.h"
#include "SurvivorStatComponent.h"
#include "SurvivorAnimInstance.h"

// Sets default values
ASurvivor::ASurvivor()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 200.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->SetRelativeLocation(FVector(0, 0, 80.0f));
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	Stat = CreateDefaultSubobject<USurvivorStatComponent>(TEXT("Stat"));

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

	bRunning = false;
	bCarried = false;
	bHanged = false;
	bTraped = false;
}

// Called when the game starts or when spawned
void ASurvivor::BeginPlay()
{
	Super::BeginPlay();

	Hp = Stat->GetHp();
	
	WalkSpeed = Stat->GetWalkSpeed();
	RunSpeed = Stat->GetRunSpeed();
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->SetCrouchedHalfHeight(200.0f);

	// Hp 2인 상태로 시작
	FDamageEvent DamageEvent;
	TakeDamage(1.0f, DamageEvent, GetController(), this);
}

void ASurvivor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SurvivorAnimInstance = Cast<USurvivorAnimInstance>(GetMesh()->GetAnimInstance());

}

// Called every frame
void ASurvivor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASurvivor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ASurvivor::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ASurvivor::MoveRight);

	// "turn" handles devices that provide an absolute delta, such as a mouse.
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis(TEXT("Interact"), this, &ASurvivor::Interact);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Released, this, &ASurvivor::EndInteract);

	PlayerInputComponent->BindAction(TEXT("StartRun"), EInputEvent::IE_Pressed, this, &ASurvivor::StartRun);
	PlayerInputComponent->BindAction(TEXT("StartRun"), EInputEvent::IE_Released, this, &ASurvivor::StopRun);

	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ASurvivor::CrouchStart);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &ASurvivor::CrouchEnd);

	PlayerInputComponent->BindAction(TEXT("Action Interact"), EInputEvent::IE_Pressed, this, &ASurvivor::ActionInteract);
}

void ASurvivor::MoveForward(float Value)
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

void ASurvivor::MoveRight(float Value)
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

void ASurvivor::StartRun()
{
	bRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ASurvivor::StopRun()
{
	bRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASurvivor::CrouchStart()
{
	Crouch();
}

void ASurvivor::CrouchEnd()
{
	UnCrouch();
}

float ASurvivor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Stat에서 Survivor의 상태를 변경
	Stat->OnAttacked(DamageAmount);

	Hp = Stat->GetHp();

	return DamageAmount;
}


void ASurvivor::SetCarried(bool state)
{
	bCarried = state;
	if (state == true)
	{
		GetCapsuleComponent()->SetGenerateOverlapEvents(false);
		SphereCollision->SetGenerateOverlapEvents(false);

		GetController()->SetIgnoreMoveInput(true);
	}
	else if (state == false)
	{
		GetCapsuleComponent()->SetGenerateOverlapEvents(true);
		SphereCollision->SetGenerateOverlapEvents(true);

		GetController()->ResetIgnoreInputFlags();
	}
}

void ASurvivor::SetHanged(bool state)
{
	bHanged = state;
	if (state == true)
	{
		Stat->IncreaseHangedCount();

		GetController()->SetIgnoreMoveInput(true);
	}
	else if (state == false)
	{
		GetController()->ResetIgnoreInputFlags();
	}
}

void ASurvivor::SetTraped(bool state)
{
	bTraped = state;
	if (state == true)
	{
		Stat->OnTrapped();
		Hp = Stat->GetHp();

		GetController()->SetIgnoreMoveInput(true);
	}
	else if (state == false)
	{
		GetController()->ResetIgnoreInputFlags();
	}
}


void ASurvivor::Interact(float Value)
{
	// Survivor와 Overlap된 Actor들 중에서 가장 가까운 Actors에 Interact
	GetOverlappingActors(OverlappingActors);

	if ((Controller != nullptr) && (Value != 0.0f) && !OverlappingActors.IsEmpty())
	{
		AActor* MinOverlappingActor = GetMinOverlappingActor();

		// Generator, ExitDoor
		if (MinOverlappingActor && (MinOverlappingActor->IsA(AGenerator::StaticClass()) || MinOverlappingActor->IsA(AExitDoor::StaticClass())) && Hp >= 2)
		{
			InteractingActor = Cast<AInteractiveActor>(MinOverlappingActor);
			if (InteractingActor)
			{
				InteractingActor->Interact();
			}

			SetSurvivorInteractLocation(MinOverlappingActor);

			bInteracting = true;
		}
		// Heal Survivor
		else if (MinOverlappingActor && MinOverlappingActor->IsA(ASurvivor::StaticClass()) && Hp >= 2)
		{
			ASurvivor* WoundedSurvivor = Cast<ASurvivor>(MinOverlappingActor);

			if (WoundedSurvivor->Stat->GetHp() <= 2)
			{
				WoundedSurvivor->Stat->Recover();

				GetCharacterMovement()->StopMovementImmediately();
				FVector ToTarget = WoundedSurvivor->GetActorLocation() - GetActorLocation();
				FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
				SetActorRotation(LookAtRotation);

				bInteracting = true;
			}
		}
		// Hook
		else if (MinOverlappingActor && MinOverlappingActor->IsA(AHook::StaticClass()) && Hp >= 2)
		{
			InteractingActor = Cast<AInteractiveActor>(MinOverlappingActor);
			AHook* Hook = Cast<AHook>(MinOverlappingActor);
			if (Hook && Hook->IsHanging())
			{
				Hook->Interact();

				GetCharacterMovement()->StopMovementImmediately();
				FVector ToTarget = InteractingActor->GetActorLocation() - GetActorLocation();
				FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
				SetActorRotation(LookAtRotation);

				bInteracting = true;
			}
		}
		// BearTrap
		else if (MinOverlappingActor && MinOverlappingActor->IsA(ABearTrap::StaticClass()))
		{
			ABearTrap* BearTrap = Cast<ABearTrap>(MinOverlappingActor);
			if (bTraped)
			{
				if (BearTrap && BearTrap->IsTraping())
				{
					BearTrap->Interact();
				}
			}
			else
			{
				if (BearTrap && !BearTrap->IsTraping() && !BearTrap->IsUsed())
				{
					BearTrap->Interact();

					bInteracting = true;
				}
			}
		}
	}
}

void ASurvivor::EndInteract()
{
	if (InteractingActor)
	{
		if (InteractingActor->IsA(AHook::StaticClass()))
		{
			InteractingActor->EndInteract();
			InteractingActor = nullptr;
		}
		else if (InteractingActor->IsA(ABearTrap::StaticClass()))
		{
			ABearTrap* BearTrap = Cast<ABearTrap>(InteractingActor);
			if (BearTrap)
			{
				BearTrap->EndInteract();
				InteractingActor = nullptr;
			}
		}
	}

	bInteracting = false;
}


void ASurvivor::ActionInteract()
{
	GetOverlappingActors(OverlappingActors);
	if (Controller != nullptr && !OverlappingActors.IsEmpty())
	{
		AActor* MinOverlappingActor = GetMinOverlappingActor();

		// 창틀
		if (MinOverlappingActor && MinOverlappingActor->IsA(AWindow::StaticClass()) && Hp >= 2)
		{
			SetSurvivorActionInteractLocation(MinOverlappingActor);

			FTimerHandle VaultTimerHandle;
			float VaultMontageDelay = SurvivorAnimInstance->PlayVaultMontage() - 0.2f;
			GetWorld()->GetTimerManager().SetTimer(VaultTimerHandle, this, &ASurvivor::EndActionInteractMontage, VaultMontageDelay);
		}
		// 판자
		else if (MinOverlappingActor && MinOverlappingActor->IsA(APallet::StaticClass()) && Hp >= 2)
		{
			APallet* Pallet = Cast<APallet>(MinOverlappingActor);
			if (Pallet->IsUsed())
			{
				SetSurvivorActionInteractLocation(MinOverlappingActor);

				FTimerHandle VaultTimerHandle;
				float VaultMontageDelay = SurvivorAnimInstance->PlayVaultMontage() - 0.2f;
				GetWorld()->GetTimerManager().SetTimer(VaultTimerHandle, this, &ASurvivor::EndActionInteractMontage, VaultMontageDelay);
			}
			else
			{
				SetSurvivorActionInteractLocation(MinOverlappingActor);

				Pallet->Interact();

				FTimerHandle PullDownTimerHandle;
				float PullDownMontageDelay = SurvivorAnimInstance->PlayPullDownMontage() - 0.2f;
				GetWorld()->GetTimerManager().SetTimer(PullDownTimerHandle, this, &ASurvivor::EndActionInteractMontage, PullDownMontageDelay);
			}
		}
	}
}

void ASurvivor::EndActionInteractMontage()
{
	InteractingActor = nullptr;

	SetActorLocation(WindowPalletInteractMoveLocation);


	GetController()->ResetIgnoreInputFlags();

	WindowPalletInteractMoveLocation = GetActorLocation();

	// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}


// 상호작용 시 생존자와 Overlap중인 가장 가까운 Actor를 반환
AActor* ASurvivor::GetMinOverlappingActor()
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

	return MinOverlappingActor;
}

// 생존자가 발전기, 출구와 상호작용했을 경우의 Location과 Rotation설정
void ASurvivor::SetSurvivorInteractLocation(AActor* MinOverlappingActor)
{
	InteractingActor = Cast<AInteractiveActor>(MinOverlappingActor);

	// Interact시 Survivor의 위치를 고정
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

	SetActorLocation(FVector(InteractLocation->GetComponentLocation().X, InteractLocation->GetComponentLocation().Y, GetActorLocation().Z));

	FVector ToTarget = InteractingActor->GetActorLocation() - GetActorLocation();
	FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
	SetActorRotation(LookAtRotation);
}

// 생존자가 창틀, 판자와 상호작용했을 경우의 Location과 Rotation설정
void ASurvivor::SetSurvivorActionInteractLocation(AActor* MinOverlappingActor)
{
	InteractingActor = Cast<AInteractiveActor>(MinOverlappingActor);

	USceneComponent* MaxDistanceLocation = nullptr;
	USceneComponent* MinDistanceLocation = nullptr;
	float MaxInteractDistance = 0.0f;
	float MinInteractDistance = 1000.0f;
	for (USceneComponent* InteractCharacterLocation : InteractingActor->InteractCharacterLocations)
	{
		float LocationDistance = FVector::Dist(GetActorLocation(), InteractCharacterLocation->GetComponentLocation());
		if (MaxInteractDistance <= LocationDistance)
		{
			MaxInteractDistance = LocationDistance;
			MaxDistanceLocation = InteractCharacterLocation;
		}
		if (MinInteractDistance >= LocationDistance)
		{
			MinInteractDistance = LocationDistance;
			MinDistanceLocation = InteractCharacterLocation;
		}
	}

	// GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorLocation(FVector(MinDistanceLocation->GetComponentLocation().X, MinDistanceLocation->GetComponentLocation().Y, GetActorLocation().Z));

	FVector ToTarget = MaxDistanceLocation->GetComponentLocation() - MinDistanceLocation->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
	SetActorRotation(LookAtRotation);

	GetCharacterMovement()->StopMovementImmediately();
	GetController()->SetIgnoreMoveInput(true);

	if (InteractingActor->IsA(APallet::StaticClass()))
	{
		APallet* Pallet = Cast<APallet>(InteractingActor);
		if (Pallet->IsUsed())
		{
			WindowPalletInteractMoveLocation = FVector(MaxDistanceLocation->GetComponentLocation().X, MaxDistanceLocation->GetComponentLocation().Y, GetActorLocation().Z);
		}
		else
		{
			WindowPalletInteractMoveLocation = FVector(MinDistanceLocation->GetComponentLocation().X, MinDistanceLocation->GetComponentLocation().Y, GetActorLocation().Z);
		}
	}
	else
	{
		WindowPalletInteractMoveLocation = FVector(MaxDistanceLocation->GetComponentLocation().X, MaxDistanceLocation->GetComponentLocation().Y, GetActorLocation().Z);
	}

}