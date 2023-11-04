// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_Fruit.h"

// Sets default values
ARhino_Fruit::ARhino_Fruit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhino_Fruit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARhino_Fruit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARhino_Fruit::SpawnFruit()
{
	SpawnPickable();
}

void ARhino_Fruit::DeSpawnFruit()
{
	DeSpawnPickable();
}
