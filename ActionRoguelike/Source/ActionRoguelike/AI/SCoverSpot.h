// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCoverSpot.generated.h"

UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCoverSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASCoverSpot();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
};
