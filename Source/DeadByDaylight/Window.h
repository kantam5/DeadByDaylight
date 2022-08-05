// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "Window.generated.h"

/**
 * 
 */
UCLASS()
class DEADBYDAYLIGHT_API AWindow : public AInteractiveActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWindow();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision;
};
