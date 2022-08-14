// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveActor.generated.h"

UCLASS()
class DEADBYDAYLIGHT_API AInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact();
	virtual void EndInteract();

	virtual void KillerInteract();
	virtual void KillerEndInteract();

	virtual bool IsBroken();

	UPROPERTY(EditAnywhere, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	USceneComponent* InteractCharacterLocation_0;

	UPROPERTY(EditAnywhere, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	USceneComponent* InteractCharacterLocation_1;

	UPROPERTY(EditAnywhere, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	USceneComponent* InteractCharacterLocation_2;

	UPROPERTY(EditAnywhere, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	USceneComponent* InteractCharacterLocation_3;

	TArray<USceneComponent*> InteractCharacterLocations;

	bool bBroken;
};
