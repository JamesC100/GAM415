// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

// Forward declarations
class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class CARPENTER415_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

	// Variables
	// Clamp the terrain size
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int XSize = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
	int YSize = 0;

	// Z axis height multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0.0))
	float ZMultiplier = 1.0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.0))
	float NoiseScale = 1.0;

	// Scale of the terrain spacing
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float Scale = 0.0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
	float UVScale = 0.0;

	// Width and Height of the terrain 
	UPROPERTY(EditAnywhere)
	float radius;

	UPROPERTY(EditAnywhere)
	FVector Depth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Setting the material for the terrain
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Mat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to alter the terrain using raytrace impact
	UFUNCTION()
	void AlterMesh(FVector impactpoint);

private:
	// Procedural mesh component that holds the generated terrain
	UProceduralMeshComponent* ProcMesh;
	// Mesh data arrays
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;

	int sectionID = 0;

	// Functions that generate mesh data
	void CreateVertices();
	void CreateTriangles();

};
