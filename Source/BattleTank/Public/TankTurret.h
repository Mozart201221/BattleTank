// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
//UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision")) // (отображение класса в BP)
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 это максимальное значение ствола при движении вниз , +1 максимальное значение скорости при подъеме
	void Rotate (float RelativeSpeed);


private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 25;
};
