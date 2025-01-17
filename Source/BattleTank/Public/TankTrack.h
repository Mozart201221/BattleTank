// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * �������� ������������ ����� ���������� ����������� �������� ���� � ��������� ��� ���� � �����
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//������������� �������� ��� ������� ����� -1 � +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	// ������������ ���� �� �������� � ��������
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; // ����� ����� 40� � ��������� � 1g

private:
	UTankTrack();

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void ApplySidewaysForce();

	void DriveTrack();

	float CurrentThrottle = 0;
};
