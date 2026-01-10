// Copyright Epic Games, Inc. All Rights Reserved.

#include "Carpenter415GameMode.h"
#include "Carpenter415Character.h"
#include "UObject/ConstructorHelpers.h"

ACarpenter415GameMode::ACarpenter415GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
