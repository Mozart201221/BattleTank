// Copyright EmbraceIT Ltd.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // должен быть включен последним

class UTankAimingComponent;

/**
 * ѕомогает игроку в его цел€х
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
	// ћетод начинает перемещать ствол танка так чтобы можно было выстрелить туда где перекрестие прицела пересекаетс€ с миром
	void AimTowardsCrosshair();

	// ¬озвращает внешний параметр, True - если попадание будет в ландшафт
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
