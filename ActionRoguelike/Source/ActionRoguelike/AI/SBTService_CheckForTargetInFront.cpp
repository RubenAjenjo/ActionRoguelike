// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTService_CheckForTargetInFront.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void USBTService_CheckForTargetInFront::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                 float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	auto BB = OwnerComp.GetBlackboardComponent();
	if (ensure(BB))
	{
		const AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			auto AIController = OwnerComp.GetAIOwner();
			if (ensure(AIController))
			{
				auto AIPawn = AIController->GetPawn();
				if (ensure(AIPawn))
				{
					FHitResult Hit;
					bool bIsInFront = false;
					TArray<AActor*> ActorsToIgnore;
					ActorsToIgnore.Add(AIPawn);
					UKismetSystemLibrary::SphereTraceSingle(
						GetWorld(),
						AIPawn->GetActorLocation() + AIPawn->GetActorForwardVector() * 50,
						AIPawn->GetActorLocation() + AIPawn->GetActorForwardVector() * 10000,
						50,
						 UEngineTypes::ConvertToTraceType(ECC_Pawn),
						false,
						ActorsToIgnore,
						EDrawDebugTrace::None,
						Hit,
						true,
						FLinearColor::Red,
						FLinearColor::Green,
						5
						);
					if (Hit.bBlockingHit)
					{
						bIsInFront = (Hit.Actor == TargetActor);
					}
					BB->SetValueAsBool(IsInFrontKey.SelectedKeyName, bIsInFront);
				}
			}
		}
	}
}
