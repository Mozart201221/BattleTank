// Copyright EmbraceIT Ltd.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // ������ ���� ������� ���������

class UTankAimingComponent;

/**
 * �������� ������ � ��� �����
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;

	void SetPawn(APawn* InPawn);

	UFUNCTION()
	void OnPossedTankDeath();

	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	// ����� �������� ���������� ����� ����� ��� ����� ����� ���� ���������� ���� ��� ����������� ������� ������������ � �����
	void AimTowardsCrosshair();

	// ���������� ������� ��������, True - ���� ��������� ����� � ��������
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333;
	
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
