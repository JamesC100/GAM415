// Fill out your copyright notice in the Description page of Project Settings.

#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve preformance if you dont need it.
	PrimaryActorTick.bCanEverTick = false;

	// Attachment setup for procedural mesh component
	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");
	ProcMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();

	// Create mesh at runtime
	CreateVertices();
	CreateTriangles();
	ProcMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true);
	ProcMesh->SetMaterial(0, Mat);
}

//Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APerlinProcTerrain::AlterMesh(FVector impactPoint)
{
	// Loop through vertices and modify those within radius of impact
	for (int i = 0; i < Vertices.Num(); i++)
	{
		FVector tempVector = impactPoint - this->GetActorLocation();

		if (FVector(Vertices[i] - tempVector).Size() < radius)
		{
			// Lower vertex by Depth amount
			Vertices[i] = Vertices[i] - Depth;
			// Update the mesh section
			ProcMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

void APerlinProcTerrain::CreateVertices()
{
	// Nested loop to create vertices based on the X and Y size
	for (int X = 0; X <= XSize; X++)
	{
		for (int Y = 0; Y <= YSize; Y++)
		{
			// Calculate the Z value using Perlin noise
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;

			// Add the vertices to the array
			Vertices.Add(FVector(X * Scale, Y * Scale, Z));

			// Add UVs for material mapping
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
		}
	}
}


void APerlinProcTerrain::CreateTriangles()
{
	// Temporary variable to keep track of current vertex
	int Vertex = 0;

	// Nested loop to create triangles based on the X and Y size
	for (int X = 0; X < XSize; X++)
	{
		for (int Y = 0; Y < YSize; Y++)
		{
			// First triangle
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);
			
			// Second triangle
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);

			// Move to next column
			Vertex++;
		}

		// Skip to next row
		Vertex++;
	}
}