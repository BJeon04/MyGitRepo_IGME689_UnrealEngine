#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"

UCLASS()
class IGME689_API ACar : public APawn
{
	GENERATED_BODY()

public:
	ACar();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Car")
	void SnapToSplineStart(class USplineComponent* Spline, float ZOffset = 0.f);

private:

	// Root component for movement/rotation
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* CarRoot;

	// NEW: MeshRoot (lets you rotate the car mesh without touching the camera)
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* MeshRoot;

	// Car mesh
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* CarMesh;

	// Wheels
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WheelFL;
    
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WheelFR;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WheelBL;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WheelBR;

	// Camera
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	// Movement
	FVector CurrentVelocity;
	float ThrottleInput;

	void MoveForward(float Value);
	void MoveRight(float Value);

	UPROPERTY(EditAnywhere)
	float Speed = 800.f;

	UPROPERTY(EditAnywhere)
	float TurnSpeed = 80.f;
};
