// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Rhino_GJ2023GameMode.generated.h"


class ARhino_SolidWall;
class ARhino_BreakableWall;

UCLASS(minimalapi)
class ARhino_GJ2023GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARhino_GJ2023GameMode();

	UPROPERTY(EditAnywhere, Category = "MazeSpawn Options")
		int32 NumberSolidWalls = 5;
	UPROPERTY(EditAnywhere, Category = "MazeSpawn Options")
		int32 NumberBreakableWalls = 5;
	UPROPERTY(EditAnywhere, Category = "MazeSpawn Options")
		int32 NumberFruits = 5;

	UFUNCTION(BlueprintCallable)
	void ScanAllObjects();
	UFUNCTION(BlueprintCallable)
	void RandomSpawnObjects();


protected:

	UPROPERTY()
	TArray<ARhino_SolidWall*> ActiveSolidWalls;
	UPROPERTY()
	TArray<ARhino_BreakableWall*> ActiveBreakableWalls;
	UPROPERTY()
	TArray<ARhino_SolidWall*> InactiveSolidWalls;
	UPROPERTY()
	TArray<ARhino_BreakableWall*> InactiveBreakableWalls;
	//TArray<ARhino_SolidWall*> Fruits;
	virtual void BeginPlay() override;

};



