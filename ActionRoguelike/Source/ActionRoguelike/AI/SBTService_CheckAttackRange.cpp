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
					bool bWithinRange = DistanceTo < 3500.f;
					bool bInLineOfSight = false;
					if (bWithinRange)
					{
						FHitResult Hit;
						FVector TargetLoc = TargetActor->GetActorLocation();
						FVector PawnEyes;
						FRotator PawnRot = AIPawn->GetActorRotation();
						AIPawn->GetActorEyesViewPoint(PawnEyes, PawnRot);
						TArray<AActor*> ActorsToIgnore;
						ActorsToIgnore.Add(AIPawn);
						UKismetSystemLibrary::SphereTraceSingle(
							GetWorld(),
							PawnEyes,
							TargetLoc,
							20.f,
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

						if (Hit.Actor == TargetActor)
							bInLineOfSight = true;
							
					}

					BB->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bInLineOfSight);
				}
			}
		}
	}
}
