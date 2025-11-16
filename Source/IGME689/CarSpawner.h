// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "CarSpawner.generated.h"

UCLASS()
class IGME689_API ACarSpawner : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACar> CarClass;

	ACar* SpawnCarAtSpline(USplineComponent* Spline);
};