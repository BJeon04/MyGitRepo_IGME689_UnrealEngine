#include "Car.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"

ACar::ACar()
{
    PrimaryActorTick.bCanEverTick = true;

    // ROOT (controls movement + rotation)
    CarRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CarRoot"));
    RootComponent = CarRoot;

    AutoPossessPlayer = EAutoReceiveInput::Player0;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(CarRoot);

    // CAMERA
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // NEW: MeshRoot (lets you rotate the mesh safely)
    MeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MeshRoot"));
    MeshRoot->SetupAttachment(CarRoot);

    // CAR MESH (attach to MeshRoot instead of CarRoot)
    CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
    CarMesh->SetupAttachment(MeshRoot);

    // WHEELS
    WheelFL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelFL"));
    WheelFL->SetupAttachment(CarMesh);

    WheelFR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelFR"));
    WheelFR->SetupAttachment(CarMesh);

    WheelBL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelBL"));
    WheelBL->SetupAttachment(CarMesh);

    WheelBR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelBR"));
    WheelBR->SetupAttachment(CarMesh);

    // CAMERA ARM (attach to CarRoot so it does NOT rotate with the mesh)
    
    SpringArm->TargetArmLength = 500.f;
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 5.f;
    SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));

   

    // Movement defaults
    Speed = 800.f;
    TurnSpeed = 80.f;
    ThrottleInput = 0.f;
}

void ACar::BeginPlay()
{
    Super::BeginPlay();
}

void ACar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!CurrentVelocity.IsZero())
    {
        FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
        SetActorLocation(NewLocation);
    }
}

void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ACar::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ACar::MoveRight);
}

void ACar::MoveForward(float Value)
{
    float Clamped = FMath::Clamp(Value, -1.f, 1.f);
    ThrottleInput = Clamped;

    // Move relative to CarRoot
    CurrentVelocity = CarRoot->GetForwardVector() * (Clamped * Speed);
}

void ACar::MoveRight(float Value)
{
    if (FMath::Abs(ThrottleInput) < 0.1f)
        return;

    float Clamped = FMath::Clamp(Value, -1.f, 1.f);

    // Rotate CarRoot (camera stays stable)
    CarRoot->AddLocalRotation(FRotator(0.f, Clamped * TurnSpeed * GetWorld()->GetDeltaSeconds(), 0.f));
}

void ACar::SnapToSplineStart(USplineComponent* Spline, float ZOffset)
{
    if (!Spline) return;

    FVector Location = Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
    FRotator Rotation = Spline->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World);

    Location.Z += ZOffset; // adjust height

    CarRoot->SetWorldLocation(Location);
    CarRoot->SetWorldRotation(Rotation);

    CurrentVelocity = FVector::ZeroVector;
    ThrottleInput = 0.f;
}
