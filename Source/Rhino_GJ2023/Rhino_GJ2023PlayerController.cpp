// Copyright Epic Games, Inc. All Rights Reserved.

#include "Rhino_GJ2023PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Rhino_GJ2023Character.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Rhino_GJ2023Character.h"

ARhino_GJ2023PlayerController::ARhino_GJ2023PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ARhino_GJ2023PlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	ControlledCharacter = Cast<ARhino_GJ2023Character>(GetCharacter());
}

void ARhino_GJ2023PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ARhino_GJ2023PlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ARhino_GJ2023PlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ARhino_GJ2023PlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ARhino_GJ2023PlayerController::OnSetDestinationReleased);

		//Setup dash event
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ARhino_GJ2023PlayerController::OnDashTriggered);
	}
}

void ARhino_GJ2023PlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ARhino_GJ2023PlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ARhino_GJ2023PlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

void ARhino_GJ2023PlayerController::OnDashTriggered()
{
	if (ControlledCharacter == nullptr) return;

	FVector CharacterDirection = ControlledCharacter->GetActorForwardVector();
	FVector LaunchVelocity = CharacterDirection * DashLaunchVelocity;

	ControlledCharacter->SetIsDashing(true);
	ControlledCharacter->LaunchCharacter(LaunchVelocity, false, false);

	GetWorldTimerManager().SetTimer(DashTimerHandle, this, &ARhino_GJ2023PlayerController::OnStopDashing, DashWindow, false);
	
}

void ARhino_GJ2023PlayerController::OnStopDashing()
{	
	if (ControlledCharacter == nullptr) return;

	ControlledCharacter->SetIsDashing(false);
}
