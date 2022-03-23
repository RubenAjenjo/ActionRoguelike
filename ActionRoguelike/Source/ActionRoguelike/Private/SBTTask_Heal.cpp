// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTTask_Heal.h"

#include "AIController.h"
#include "SCharacterBase.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto AIController = OwnerComp.GetAIOwner();
	if (ensure(AIController))
	{
		if (ASCharacterBase* AICharacter = Cast<ASCharacterBase>(AIController->GetPawn()))
		{
			const float LostHealth = 100.f - AICharacter->GetHealthAmount();
			AICharacter->AddHealth(LostHealth);
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
