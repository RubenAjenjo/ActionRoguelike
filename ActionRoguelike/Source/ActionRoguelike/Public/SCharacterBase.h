// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SHealthComponent.h"
#include "GameFramework/Character.h"
#include "SCharacterBase.generated.h"

class USHealthComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacterBase();

	FORCEINLINE float GetHealthAmount() const { return HealthComponent->GetHealth();}
	FORCEINLINE void AddHealth(float HealthAmount) { HealthComponent->ChangeHealth(HealthAmount);}
protected:

	UPROPERTY(BlueprintReadOnly)
	USHealthComponent* HealthComponent;
};
