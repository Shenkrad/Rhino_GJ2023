// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_UpdatePositionToRun.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTS_UpdatePositionToRun::UBTS_UpdatePositionToRun()
{
    NodeName = TEXT("Update Position to Run");
}

void UBTS_UpdatePositionToRun::OnGameplayTaskActivated(class UGameplayTask& Task)
{
    // Implement if needed
}

void UBTS_UpdatePositionToRun::OnGameplayTaskDeactivated(class UGameplayTask& Task)
{
    // Implement if needed
}

void UBTS_UpdatePositionToRun::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if (PlayerPawn == nullptr) return;
    FVector AIPosition = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
    FVector PlayerPosition = PlayerPawn->GetActorLocation();

    FVector DirectionToPlayer = PlayerPosition - AIPosition;
    DirectionToPlayer.Normalize();

    float DistanceToMove = 600.f;
    FVector NewAIPosition = AIPosition -DirectionToPlayer * DistanceToMove;


    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NewAIPosition);
}

