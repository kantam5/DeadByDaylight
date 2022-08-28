// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivorStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADBYDAYLIGHT_API USurvivorStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USurvivorStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetMaxHp(int32 MaxHp);
	void OnAttacked(float DamageAmount);

	void OnTrapped();

	int32 GetHp() { return Hp; }
	float GetWalkSpeed() { return WalkSpeed; }
	float GetRunSpeed() { return RunSpeed; }
	float GetCrawlSpeed() { return CrawlSpeed; }

	void Recover();

	void IncreaseHangingTime();
	void ResetHangingTime() { HangingTime = 0.0f; };

	int32 IncreaseHangedCount();

private:
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Hp;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float WalkSpeed;
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float RunSpeed;
	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CrawlSpeed;

	UPROPERTY(VisibleAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 HangedCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float MaxRecoverProgress;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float RecoverProgress;
	bool bRecovered;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float MaxHangingTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float HangingTime;

	class ASurvivor* Survivor;
};
