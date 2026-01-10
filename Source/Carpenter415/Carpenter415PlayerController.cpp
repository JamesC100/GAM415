// Copyright Epic Games, Inc. All Rights Reserved.


#include "Carpenter415PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void ACarpenter415PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}