// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RicochetEffect.h"
#include "ProjectileEffectComponent.h"
#include "GameFramework/Pawn.h"


// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileActor::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.0f;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	ProjectileStrength = -1;
	CurrentStrength = ProjectileStrength;
	DamageAmount = 500;
	ProjectileSpeed = 3000.0f;

	//ProjectileSpecialComponent = CreateDefaultSubobject<UProjectileEffectComponent>(TEXT("ProjectileSpecial0"));

}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	Origin = GetActorLocation();

	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;

	TArray<UProjectileEffectComponent*> comp;
	GetComponents(comp);
	if (comp.Num() > 0)
	{
		ProjectileSpecialComponent = comp[0];
		ProjectileSpecialComponent->SetProjectile(this);
	}
	
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FVector::Distance(Origin, GetActorLocation()) > Range)
	{
		OnProjectileDestroy();
	}

}

void AProjectileActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	if (OtherActor)
	{
		APawn* Hit = Cast<APawn>(OtherActor);

		if (Hit)
		{
			HitPawn = Hit;
		}
	}

	if (ProjectileSpecialComponent != nullptr)
	{
		ProjectileSpecialComponent->ActivateHitEffect();

	}
	else
	{
		//Projectile auto destroys if strength is set to -1
		if (ProjectileStrength == -1)
			OnProjectileDestroy();
	}
}

void AProjectileActor::OnProjectileDestroy()
{
	Destroy();
}

