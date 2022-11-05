// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "HyperDrivePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component for the projectile sphere
	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMeshComponent->SetupAttachment(RootComponent);
	PickupMeshComponent->BodyInstance.SetCollisionProfileName("Trigger");
	RootComponent = PickupMeshComponent;

}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupActor::PickupResponse(AHyperDrivePawn* Player)
{
}

void APickupActor::PlayPickupSound()
{
	/*if (PickupEvent != nullptr)
	{
		FAkAudioDevice::Get()->PostEvent(PickupEvent,this);
	}*/

	if (PickupSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}
}

