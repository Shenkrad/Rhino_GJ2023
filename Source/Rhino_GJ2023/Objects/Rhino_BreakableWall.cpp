// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_BreakableWall.h"

// Sets default values
ARhino_BreakableWall::ARhino_BreakableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhino_BreakableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARhino_BreakableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

