// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

 void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Перемещаем пушку на верный объем в этом кадре
	// С данной максимальной скоростью подъема и временем кадра
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}