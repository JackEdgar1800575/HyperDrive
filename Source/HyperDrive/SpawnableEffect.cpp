// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableEffect.h"
#include "Kismet/GameplayStatics.h"

USpawnableEffect::USpawnableEffect()
{
	bHitActionOnDestroy = true;
	bAutoDestroy = false;
}

void USpawnableEffect::ActivateHitEffect()
{
	if (SpawnObject != nullptr)
	{
		//Spawn the specified actor where the projectile currently is
		GetWorld()->SpawnActor<AActor>(SpawnObject, Projectile->GetActorLocation(), Projectile->GetActorRotation());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("What the fuck do you want me to spawn dipshit!?"));
	}

	Projectile->Destroy();
}

void USpawnableEffect::ActivateDestroyEffect()
{
	Super::ActivateDestroyEffect();
}

