// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_NPCCharacter.h"

// Sets default values
ARhino_NPCCharacter::ARhino_NPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhino_NPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARhino_NPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARhino_NPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

