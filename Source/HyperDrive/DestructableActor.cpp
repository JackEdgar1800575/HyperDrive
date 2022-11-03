// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructableActor.h"
#include "ProjectileActor.h"
#include "Engine/StaticMesh.h"
#include "../Plugins/Wwise/Source/AkAudio/Classes/AkGameplayStatics.h"

// Sets default values
ADestructableActor::ADestructableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Destructible Mesh"));
	RootComponent = MeshComponent;

	DefaultHealth = 20;
	CurrentHealth = DefaultHealth;

}

// Called when the game starts or when spawned
void ADestructableActor::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent->OnComponentHit.AddDynamic(this, &ADestructableActor::OnHit);

}

void ADestructableActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		AProjectileActor* Proj = Cast<AProjectileActor>(OtherActor);

		/*if (HitSoundEvent != nullptr)
		{
			FAkAudioDevice::Get()->PostEvent(HitSoundEvent, this);
		}*/


		if (Proj)
		{
			TakeDamage(Proj->DamageAmount);
		}
	}
}

// Called every frame
void ADestructableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructableActor::TakeDamage(int InDmg)
{
	CurrentHealth -= InDmg;

	if (CurrentHealth <= 0)
	{
		OnDestroy();
	}
}

void ADestructableActor::OnDestroy()
{
	////Play Audio of Object Destroying
	if (DestroyEvent != nullptr)
	{
		FAkAudioDevice::Get()->PostEvent(DestroyEvent, this);
	}
	Destroy();
}

