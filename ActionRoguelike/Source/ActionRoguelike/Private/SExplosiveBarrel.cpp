// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include <Components/BoxComponent.h>
#include <PhysicsEngine/RadialForceComponent.h>
#include <particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	StaticMeshComp->SetupAttachment(RootComponent);

	StaticMeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnHit);


	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->SetupAttachment(StaticMeshComp);
	RadialForceComp->bIgnoreOwningActor = true;

}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
	StaticMeshComp->SetPhysicsLinearVelocity(FVector::UpVector * 1000.f);
	StaticMeshComp->SetPhysicsAngularVelocity(FVector(FMath::RandRange(-10.2f, 10.2f), FMath::RandRange(-10.2f, 10.2f), FMath::RandRange(-10.2f, 10.2f)));
	StaticMeshComp->OnComponentHit.RemoveAll(this);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorTransform());
	auto PartSysComp = UGameplayStatics::SpawnEmitterAttached(FireParticles, StaticMeshComp);
}
// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

