// Fill out your copyright notice in the Description page of Project Settings.


#include "Killer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"
#include "KillerAnimInstance.h"

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
