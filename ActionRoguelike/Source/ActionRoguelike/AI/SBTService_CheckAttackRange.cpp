// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
					bool bWithinRange = DistanceTo < 1500.f;
					bool bInLineOfSight = false;
					if (bWithinRange)
					{
						bInLineOfSight = AIController->LineOfSightTo(TargetActor);
					}

					BB->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bInLineOfSight);
				}
			}
		}
	}
}
