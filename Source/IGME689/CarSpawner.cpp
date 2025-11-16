// Fill out your copyright notice in the Description page of Project Settings.


#include "CarSpawner.h"
#include "Car.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"

ACar* ACarSpawner::SpawnCarAtSpline(USplineComponent* Spline)
{
	if (!CarClass || !Spline) return nullptr;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Temporary location (will snap after)
	ACar* Car = GetWorld()->SpawnActor<ACar>(CarClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);

	if (Car)
	{
		Car->SnapToSplineStart(Spline);

		// Possess the car
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
			PC->Possess(Car);
	}

	return Car;
}
