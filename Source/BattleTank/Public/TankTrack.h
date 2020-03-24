// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * ТанкТрак используется чтобы установить максимально движущую силу и применять эти силы к танку
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//Устанавливаем значение для привода между -1 и +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	// Максимальная сила на гусеницу в Ньютонах
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; // Масса танка 40т и ускорение в 1g

private:
	UTankTrack();

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void ApplySidewaysForce();

	void DriveTrack();

	float CurrentThrottle = 0;
};
