// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Carpenter415Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");

	// Root is the trigger volume so overlap events drive teleport functionality
	RootComponent = boxComp;
	// Mesh attached to the trigger
	mesh->SetupAttachment(boxComp);
	// Scene capture so we can position it relative to the portal
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent);
	// Attach the arrow to the root indicating the forward spawn direction
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	// Bind overlap to trigger teleport when the player enters
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverLapBegin);
	mesh->SetHiddenInSceneCapture(true);

	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePortals();

}

// Bind overlap to trigger teleport when the player enters the portal
void APortal::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only teleport the player character 
	ACarpenter415Character* playerchar = Cast<ACarpenter415Character>(OtherActor);

	// Teleport requires a linked destination
	if (playerchar)
	{
		if (OtherPortal)
		{
			// Prevent immediate re-triggering
			if (!playerchar->isTeleporting)
			{
				playerchar->isTeleporting = true;
				// Moves player to the destination
				FVector loc = OtherPortal->rootArrow->GetComponentLocation();
				playerchar->SetActorLocation(loc);

				// Timer resets the teleport lockout after a short delay
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerchar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);
			}
		} 
	}
}

void APortal::SetBool(ACarpenter415Character* playerChar)
{
	// Re-enables teleporting after the cooldown delay.
	if (playerChar)
	{
		playerChar->isTeleporting = false;
	}
}

void APortal::UpdatePortals()
{
	// Relative offset between this portal and the linked portal
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();
	// Player camera transform
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();
	// Move the capture camera so it mirrors the player camera on the linked portal side
	FVector CombinedLocation = camLocation + Location;

	// Apply the updated transform to the scene capture
	sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);
}

