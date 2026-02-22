// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Portal.generated.h"

class Carpenter415Character;

UCLASS()
class CARPENTER415_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Portal surface mesh.
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	// Captures scene from destination portal viewpoint
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* sceneCapture;

	UPROPERTY(EditAnywhere)
	UArrowComponent* rootArrow;

	// Texture that receives the scene capture output
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* renderTarget;

	// Trigger volume to detects player overlap for teleporting
	UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp;

	// Linked portal reference
	UPROPERTY(EditAnywhere)
	APortal* OtherPortal;

	// Material applied to the portal mesh
	UPROPERTY(EditAnywhere)
	UMaterialInterface* mat;

	UFUNCTION()
	void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Controls overlap to prevent repeat triggers
	UFUNCTION()
	void SetBool(ACarpenter415Character* playerChar);

	// Updates the portal rendering logic each frame
	UFUNCTION()
	void UpdatePortals();
};
