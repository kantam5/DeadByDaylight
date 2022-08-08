// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "InteractiveActor.h"
#include "SurvivorStatComponent.h"
#include "Window.h"
#include "Math/UnrealMathUtility.h"
#include "SurvivorAnimInstance.h"
#include "Pallet.h"
#include "Components/SphereComponent.h"

// Sets default values
ASurvivor::ASurvivor()
{
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

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stat = CreateDefaultSubobject<USurvivorStatComponent>(TEXT("Stat"));
	WalkSpeed = 600.0f;
	RunSpeed = 1200.0f;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASurvivor::BeginPlay()
{
	Super::BeginPlay();

	Hp = Stat->GetHp();
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

	PlayerInputComponent->BindAction(TEXT("Vault"), EInputEvent::IE_Pressed, this, &ASurvivor::Vault);

	PlayerInputComponent->BindAction(TEXT("Pull Down"), EInputEvent::IE_Pressed, this, &ASurvivor::PullDown);
}

float ASurvivor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Stat에서 Survivor의 상태를 변경
	Stat->OnAttacked(DamageAmount);

	Hp = Stat->GetHp();

	return DamageAmount;
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

void ASurvivor::Interact(float Value)
{
	// Survivor와 Overlap된 Actor들 중에서 가장 가까운 Actors에 Interact
	GetOverlappingActors(OverlappingActors);

	if ((Controller != nullptr) && (Value != 0.0f) && !OverlappingActors.IsEmpty())
	{
		// 가장 가까운 InteractingActor
		AActor* InteractingActor = nullptr;
		float MinDistance = 5000.0f;

		if (!OverlappingActors.IsEmpty())
		{
			for (AActor* OverlappingActor : OverlappingActors)
			{
				float ActorDistance = FVector::Dist(GetActorLocation(), OverlappingActor->GetActorLocation());
				if (MinDistance > ActorDistance)
				{
					MinDistance = ActorDistance;
					InteractingActor = OverlappingActor;
				}
			}
		}

		if (InteractingActor && InteractingActor->IsA(AInteractiveActor::StaticClass()) && Stat->GetHp() >= 2)
		{
			AInteractiveActor* Actor = Cast<AInteractiveActor>(InteractingActor);
			if (Actor)
			{
				Actor->Interact();
			}

			// Interact시 Survivor의 위치를 고정
			USceneComponent* InteractLocation = nullptr;
			float MinInteractDistance = 1000.0f;
			if (!InteractLocation)
			{
				for (USceneComponent* InteractCharacterLocation : Actor->InteractCharacterLocations)
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

			FVector ToTarget = Actor->GetActorLocation() - GetActorLocation();
			FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
			SetActorRotation(LookAtRotation);

			bInteracting = true;
		}
		else if (InteractingActor && InteractingActor->IsA(ASurvivor::StaticClass()) && Stat->GetHp() >= 2)
		{
			ASurvivor* WoundedSurvivor = Cast<ASurvivor>(InteractingActor);

			if (WoundedSurvivor)
			{
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
		}
	}
}

void ASurvivor::EndInteract()
{
	bInteracting = false;
}

void ASurvivor::Vault()
{
	// 오버랩 되면은 창틀의 반대방향으로 넘어간다. 
	// 창틀에서 플레이어보다 먼 위치의 반대방향의 방향으로 점점 이동하는 코드
	// 달릴 때 넘으면 더 빨리 넘도록 설정
	
	GetOverlappingActors(OverlappingActors);
	if (Controller != nullptr && !OverlappingActors.IsEmpty())
	{
		// 가장 가까운 InteractingActor
		AActor* InteractingActor = nullptr;
		AWindow* Window = nullptr;
		float MinDistance = 5000.0f;

		if (!OverlappingActors.IsEmpty())
		{
			for (AActor* OverlappingActor : OverlappingActors)
			{
				float ActorDistance = FVector::Dist(GetActorLocation(), OverlappingActor->GetActorLocation());
				if (MinDistance > ActorDistance)
				{
					MinDistance = ActorDistance;
					InteractingActor = OverlappingActor;
				}
			}
			if (InteractingActor)
			{
				Window = Cast<AWindow>(InteractingActor);
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
					FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
					SetActorRotation(LookAtRotation);

					GetCharacterMovement()->StopMovementImmediately();
					APlayerController* PlayerController = Cast<APlayerController>(GetController());
					PlayerController->SetIgnoreMoveInput(true);

					FTimerHandle VaultTimerHandle;
					float VaultMontageDelay = SurvivorAnimInstance->PlayVaultMontage() - 0.2f;
					WindowPalletInteractMoveLocation = FVector(MoveLocation->GetComponentLocation().X, MoveLocation->GetComponentLocation().Y, GetActorLocation().Z);
					GetWorld()->GetTimerManager().SetTimer(VaultTimerHandle, this, &ASurvivor::EndVaultMontage, VaultMontageDelay);
				}
			}
		}
	}
}

void ASurvivor::EndVaultMontage()
{
	SetActorLocation(WindowPalletInteractMoveLocation);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->SetIgnoreMoveInput(false);

	WindowPalletInteractMoveLocation = GetActorLocation();
}

void ASurvivor::PullDown()
{
	GetOverlappingActors(OverlappingActors);
	if (Controller != nullptr && !OverlappingActors.IsEmpty())
	{
		// 가장 가까운 InteractingActor
		AActor* InteractingActor = nullptr;
		APallet* Pallet = nullptr;
		float MinDistance = 5000.0f;

		if (!OverlappingActors.IsEmpty())
		{
			for (AActor* OverlappingActor : OverlappingActors)
			{
				float ActorDistance = FVector::Dist(GetActorLocation(), OverlappingActor->GetActorLocation());
				if (MinDistance > ActorDistance)
				{
					MinDistance = ActorDistance;
					InteractingActor = OverlappingActor;
				}
			}
			if (InteractingActor)
			{
				Pallet = Cast<APallet>(InteractingActor);
				if (Pallet)
				{
					USceneComponent* MaxDistanceLocation = nullptr;
					USceneComponent* MinDistanceLocation = nullptr;
					if (!Pallet->GetUsed())
					{
						float MaxInteractDistance = 0.0f;
						float MinInteractDistance = 1000.0f;
						for (USceneComponent* InteractCharacterLocation : Pallet->InteractCharacterLocations)
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

						SetActorLocation(FVector(MinDistanceLocation->GetComponentLocation().X, MinDistanceLocation->GetComponentLocation().Y, GetActorLocation().Z));

						FVector ToTarget = MaxDistanceLocation->GetComponentLocation() - MinDistanceLocation->GetComponentLocation();
						FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
						SetActorRotation(LookAtRotation);

						GetCharacterMovement()->StopMovementImmediately();
						APlayerController* PlayerController = Cast<APlayerController>(GetController());
						PlayerController->SetIgnoreMoveInput(true);

						Pallet->Interact();

						FTimerHandle PullDownTimerHandle;
						float PullDownMontageDelay = SurvivorAnimInstance->PlayPullDownMontage() - 0.2f;
						WindowPalletInteractMoveLocation = FVector(MinDistanceLocation->GetComponentLocation().X, MinDistanceLocation->GetComponentLocation().Y, GetActorLocation().Z);
						GetWorld()->GetTimerManager().SetTimer(PullDownTimerHandle, this, &ASurvivor::EndVaultMontage, PullDownMontageDelay);
					}
					else if (Pallet->GetUsed())
					{
						float MaxInteractDistance = 0.0f;
						float MinInteractDistance = 1000.0f;
						for (USceneComponent* InteractCharacterLocation : Pallet->InteractCharacterLocations)
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

						GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
						GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
						SetActorLocation(FVector(MinDistanceLocation->GetComponentLocation().X, MinDistanceLocation->GetComponentLocation().Y, GetActorLocation().Z));

						FVector ToTarget = MaxDistanceLocation->GetComponentLocation() - MinDistanceLocation->GetComponentLocation();
						FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
						SetActorRotation(LookAtRotation);

						GetCharacterMovement()->StopMovementImmediately();
						APlayerController* PlayerController = Cast<APlayerController>(GetController());
						PlayerController->SetIgnoreMoveInput(true);

						FTimerHandle VaultTimerHandle;
						float VaultMontageDelay = SurvivorAnimInstance->PlayVaultMontage() - 0.2f;
						WindowPalletInteractMoveLocation = FVector(MaxDistanceLocation->GetComponentLocation().X, MaxDistanceLocation->GetComponentLocation().Y, GetActorLocation().Z);
						GetWorld()->GetTimerManager().SetTimer(VaultTimerHandle, this, &ASurvivor::EndVaultMontage, VaultMontageDelay);
					}
				}
			}
		}
	}
}

void ASurvivor::EndPullDownMontage()
{
	SetActorLocation(WindowPalletInteractMoveLocation);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->SetIgnoreMoveInput(false);

	WindowPalletInteractMoveLocation = GetActorLocation();
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

bool ASurvivor::IsRunning()
{
	return bRunning;
}

bool ASurvivor::IsInteracting()
{
	return bInteracting;
}
