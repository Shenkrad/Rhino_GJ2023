// Copyright Epic Games, Inc. All Rights Reserved.

#include "Rhino_GJ2023GameMode.h"
#include "Rhino_GJ2023PlayerController.h"
#include "Rhino_GJ2023Character.h"
#include "UObject/ConstructorHelpers.h"

ARhino_GJ2023GameMode::ARhino_GJ2023GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARhino_GJ2023PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}