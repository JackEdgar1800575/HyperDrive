// Copyright Epic Games, Inc. All Rights Reserved.

#include "HyperDriveGameMode.h"
#include "HyperDrivePawn.h"

AHyperDriveGameMode::AHyperDriveGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AHyperDrivePawn::StaticClass();
}

