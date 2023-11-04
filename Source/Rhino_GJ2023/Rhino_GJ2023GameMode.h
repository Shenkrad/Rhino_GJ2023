// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Rhino_GJ2023GameMode.generated.h"


class ARhino_SolidWall;
class ARhino_BreakableWall;
class ARhino_Fruit;

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
	UPROPERTY(EditAnywhere, Category = "Fruits Options")
		float FruitTimeToRespawn = 2.5f;

	UFUNCTION(BlueprintCallable)
		void ScanAllObjects();
	UFUNCTION(BlueprintCallable)
		void RandomSpawnObjects();
	UFUNCTION()
		void RequestFruitRespawn(ARhino_Fruit* CollectedFruit); 
	UFUNCTION()
		void RequestWallDestroy(ARhino_BreakableWall* DestroyedWall);


protected:

	UPROPERTY()
	TArray<ARhino_SolidWall*> ActiveSolidWalls;
	UPROPERTY()
	TArray<ARhino_BreakableWall*> ActiveBreakableWalls;
	UPROPERTY()
	TArray<ARhino_Fruit*> ActiveFruits;
	UPROPERTY()
	TArray<ARhino_SolidWall*> InactiveSolidWalls;
	UPROPERTY()
	TArray<ARhino_BreakableWall*> InactiveBreakableWalls;
	UPROPERTY()
	TArray<ARhino_Fruit*> InactiveFruits;


	virtual void BeginPlay() override;

	UFUNCTION()
	void FruitRespawn(ARhino_Fruit* CollectedFruit);

	UFUNCTION()
		void WallDestroy(ARhino_BreakableWall* DestroyedWall);

};



