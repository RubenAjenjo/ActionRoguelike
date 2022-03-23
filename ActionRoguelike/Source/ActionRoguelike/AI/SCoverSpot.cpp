// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoverSpot.h"

// Sets default values
ASCoverSpot::ASCoverSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

}


