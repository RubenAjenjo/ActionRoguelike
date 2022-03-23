// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTService_CheckForLowHealth.h"

#include "AIController.h"
#include "SCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckForLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
				if (ASCharacterBase* AICharacter = Cast<ASCharacterBase>(AIController->GetPawn()))
				{
					if (AICharacter->GetHealthAmount() < 40.f)
						BB->SetValueAsBool(IsLowHealthKey.SelectedKeyName, true);
					else
						BB->SetValueAsBool(IsLowHealthKey.SelectedKeyName, false);
				}
			}
		}
	}
}
