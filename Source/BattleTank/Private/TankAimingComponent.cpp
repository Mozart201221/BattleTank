// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// Для того чтобы первый выстрел можно было сделать после начальной перезарядки
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	TankBarrel = BarrelToSet;
	TankTurret = TurretToSet;
}

bool UTankAimingComponent::IsTankBarrelMoving()
{
	if (!ensure(TankBarrel)) { return false; }
	auto TankBarrelForward = TankBarrel->GetForwardVector();
	return !TankBarrelForward.Equals(AimDirection, 0.001); //Вернуть булевое значение в котором вектор не равен
	
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsTankBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	// Обработать состояние наведения прицела и захвата цели
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}


void UTankAimingComponent::AimAt(FVector OutHitLocation)
{
	if (!ensure(TankBarrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // параметр должен присутствовать чтобы предотвратить баг (Баг в том, что не в каждом кадре происходит прицеливание)
	);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
			
	}
	
	// если решения не найдено, то ничего не делать
}

void UTankAimingComponent::MoveBarrelTowards(FVector TargetAimDirection)
{
	if (!ensure(TankBarrel) || !ensure(TankTurret)) { return; }
	// Вычислить разницу между текущим поворотом пушки и вектором AimDirerction
	auto BarrelRotator = TankBarrel->GetForwardVector().Rotation();
	auto AimAsRotator = TargetAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	// всегда самый кратчайший путь для рысканья
	 TankBarrel->Elevate(DeltaRotator.Pitch); 
	 if (FMath::Abs(DeltaRotator.Yaw) < 180)
	 {
		 TankTurret->Rotate(DeltaRotator.Yaw);
	 }
	 else
	 {
		 TankTurret->Rotate(-DeltaRotator.Yaw);
	 }
}

void UTankAimingComponent::Fire()
{
	
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{

		// иначе порождаем снаряд у расположение сокета на стволе
		if (!ensure(TankBarrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint, 
			TankBarrel->GetSocketLocation(FName("Projectile")),
			TankBarrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}
