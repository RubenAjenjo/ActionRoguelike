// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthComponent.h"

#include "DrawDebugHelpers.h"
#include "MovieSceneTracksPropertyTypes.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

USHealthComponent::USHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called every frame
void USHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector TextLoc = GetOwner()->GetActorLocation();

	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		TextLoc += FVector::UpVector * (Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 30.f);
	}
	DrawDebugString(GetWorld(), TextLoc, FString::Printf(TEXT("%f"), Health), 0, FColor::Red, 0);

	if (Health <= 0.f)
		GetOwner()->Destroy();
}

