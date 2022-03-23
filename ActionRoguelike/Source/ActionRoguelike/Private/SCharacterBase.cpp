// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacterBase.h"

#include "SHealthComponent.h"

// Sets default values
ASCharacterBase::ASCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<USHealthComponent>("HealthComp");
}

