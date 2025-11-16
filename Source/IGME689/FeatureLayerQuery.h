// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "FeatureLayerQuery.generated.h"



USTRUCT(BlueprintType)
struct FGeometries
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere);
	TArray<float> geometry;
};

USTRUCT(BlueprintType)
struct FProperties
{
	GENERATED_BODY()
/*public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FString> Properties;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FGeometries> Geometries;*/
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Properties")
	int32 altitude;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Properties")
	int32 length;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,  Category = "Properties")
	FString location;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Geometry")
	TArray<FGeometries> geometries;
};

UCLASS()
class IGME689_API AFeatureLayerQuery : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFeatureLayerQuery();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessfullyConnected);
	virtual void ProcessRequest();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FProperties> features;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString weblink = "";
};
