// Copyright Epic Games, Inc. All Rights Reserved.

#include "Rhino_GJ2023GameMode.h"
#include "Rhino_GJ2023PlayerController.h"
#include "Rhino_GJ2023Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/Gameplaystatics.h"

#include "Objects/Rhino_BreakableWall.h"
#include "Objects/Rhino_SolidWall.h"
#include "Objects/Rhino_Fruit.h"

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

void ARhino_GJ2023GameMode::BeginPlay()
{
	Super::BeginPlay();

	ScanAllObjects();
	RandomSpawnObjects();
}

void ARhino_GJ2023GameMode::ScanAllObjects()
{

	InactiveSolidWalls.Empty();
	InactiveBreakableWalls.Empty();
	InactiveFruits.Empty();

	TArray<AActor*> Generic;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARhino_SolidWall::StaticClass(), Generic);
	for (int i = 0; i < Generic.Num(); i++)
	{
		if (Generic.IsValidIndex(i) && Generic[i] != nullptr)
		{
			if (ARhino_SolidWall* Wall = Cast<ARhino_SolidWall>(Generic[i]))
			{
				Wall->DeSpawnWall();
				InactiveSolidWalls.Add(Wall);
			}
		}
	}

	Generic.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARhino_BreakableWall::StaticClass(), Generic);
	for (int i = 0; i < Generic.Num(); i++)
	{
		if (Generic.IsValidIndex(i) && Generic[i] != nullptr)
		{
			if (ARhino_BreakableWall* Wall = Cast<ARhino_BreakableWall>(Generic[i]))
			{
				Wall->DeSpawnWall();
				InactiveBreakableWalls.Add(Wall);
			}
		}
	}

	Generic.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARhino_Fruit::StaticClass(), Generic);
	for (int i = 0; i < Generic.Num(); i++)
	{
		if (Generic.IsValidIndex(i) && Generic[i] != nullptr)
		{
			if (ARhino_Fruit* Fruit = Cast<ARhino_Fruit>(Generic[i]))
			{
				Fruit->DeSpawnFruit();
				InactiveFruits.Add(Fruit);
			}
		}
	}
}

void ARhino_GJ2023GameMode::RandomSpawnObjects()
{

	ActiveSolidWalls.Empty();
	ActiveBreakableWalls.Empty();
	ActiveFruits.Empty();

	for (int i = 0; i < NumberSolidWalls; i++)
	{
		if (InactiveSolidWalls.IsEmpty())
			break;

		int32 Seed = FMath::RandRange(0, InactiveSolidWalls.Num() - 1);
		if (InactiveSolidWalls.IsValidIndex(i) && InactiveSolidWalls[i] != nullptr)
		{
			InactiveSolidWalls[i]->SpawnWall();
			ActiveSolidWalls.Add(InactiveSolidWalls[i]);
			InactiveSolidWalls.RemoveAt(Seed);
		}
	}

	for (int i = 0; i < NumberBreakableWalls; i++)
	{
		if (InactiveBreakableWalls.IsEmpty())
			break;

		int32 Seed = FMath::RandRange(0, InactiveBreakableWalls.Num() - 1);
		if (InactiveBreakableWalls.IsValidIndex(i) && InactiveBreakableWalls[i] != nullptr)
		{
			InactiveBreakableWalls[i]->SpawnWall();
			ActiveBreakableWalls.Add(InactiveBreakableWalls[i]);
			InactiveBreakableWalls.RemoveAt(Seed);
		}
	}

	for (int i = 0; i < NumberFruits; i++)
	{
		if (InactiveFruits.IsEmpty())
			break;

		int32 Seed = FMath::RandRange(0, InactiveFruits.Num() - 1);
		if (InactiveFruits.IsValidIndex(i) && InactiveFruits[i] != nullptr)
		{
			InactiveFruits[i]->SpawnFruit();
			ActiveFruits.Add(InactiveFruits[i]);
			InactiveFruits.RemoveAt(Seed);
		}
	}
}