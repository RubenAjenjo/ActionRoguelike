// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTService_LookAtTarget.h"

#include "AIController.h"
#include "SCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"



void USBTService_LookAtTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto BB = OwnerComp.GetBlackboardComponent();
	if (ensure(BB))
	{
		const AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TargetKey.SelectedKeyName));
		if (TargetActor)
		{
			const AAIController* AIController = OwnerComp.GetAIOwner();
			if (ensure(AIController))
			{
				if (ASCharacterBase* AICharacter = Cast<ASCharacterBase>(AIController->GetPawn()))
				{
					//Calculates the lookat rotation from direction vector
					const FVector Direction = (TargetActor->GetActorLocation()- AICharacter->GetActorLocation()).GetSafeNormal();
					const FRotator LookAtRotator = FRotationMatrix::MakeFromX(Direction).Rotator();
					AICharacter->SetActorRotation(LookAtRotator);
				}
			}
		}
	}
}
