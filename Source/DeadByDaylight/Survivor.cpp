// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "InteractiveActor.h"

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

	WalkSpeed = 600.0f;
	RunSpeed = 1200.0f;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called when the game starts or when spawned
void ASurvivor::BeginPlay()
{
	Super::BeginPlay();
	
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

	PlayerInputComponent->BindAction(TEXT("StartRun"), EInputEvent::IE_Pressed, this, &ASurvivor::StartRun);
	PlayerInputComponent->BindAction(TEXT("StartRun"), EInputEvent::IE_Released, this, &ASurvivor::StopRun);

	PlayerInputComponent->BindAxis(TEXT("Interact"), this, &ASurvivor::Interact);
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
	GetOverlappingActors(OverlappingActors);

	if ((Controller != nullptr) && (Value != 0.0f) && OverlappingActors.Num() != 0)
	{
		AActor* InteractingActor = nullptr;
		float MinDistance = 1000.0f;

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

		if (InteractingActor)
		{
			AInteractiveActor* Actor = Cast<AInteractiveActor>(InteractingActor);
			
			Actor->Interact();

			USceneComponent* InteractLocation = nullptr;
			float MinInteractDistance = 1000.0f;
			for (USceneComponent* InteractCharacterLocation : Actor->InteractCharacterLocations)
			{
				float LocationDistance = FVector::Dist(GetActorLocation(), InteractCharacterLocation->GetComponentLocation());
				if (MinInteractDistance > LocationDistance)
				{
					MinInteractDistance = LocationDistance;
					InteractLocation = InteractCharacterLocation;
				}
			}

			SetActorLocation(FVector(InteractLocation->GetComponentLocation().X, InteractLocation->GetComponentLocation().Y, GetActorLocation().Z));

			FVector ToTarget = Actor->GetActorLocation() - GetActorLocation();
			FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
			SetActorRotation(LookAtRotation);
		}
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

bool ASurvivor::IsRunning()
{
	return bRunning;
}