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
	if (HitSpawnObject != nullptr)
	{
		//Spawn the specified actor where the projectile currently is
		GetWorld()->SpawnActor<AActor>(HitSpawnObject, Projectile->GetActorLocation(), Projectile->GetActorRotation());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("What the fuck do you want me to spawn dipshit!?"));
	}

	Projectile->Destroy();
	this->Deactivate();
}

void USpawnableEffect::ActivatePawnResponse()
{
	Super::ActivatePawnResponse();

	if (!Projectile->IsPendingKillPending())
	{
		if (PawnHitSpawnObject != nullptr)
		{
			GetWorld()->SpawnActor<AActor>(PawnHitSpawnObject, Projectile->GetActorLocation(), Projectile->GetActorRotation());
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("What the fuck do you want me to spawn dipshit!?"));
		}
	}
	Projectile->Destroy();
	this->Deactivate();

}

void USpawnableEffect::ActivateDestroyEffect()
{
	Super::ActivateDestroyEffect();

	if (!Projectile->IsPendingKillPending())
	{
		if (DestroySpawnObject != nullptr)
		{
			GetWorld()->SpawnActor<AActor>(DestroySpawnObject, Projectile->GetActorLocation(), Projectile->GetActorRotation());
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("What the fuck do you want me to spawn dipshit!?"));
		}
	}
	Projectile->Destroy();
	this->Deactivate();

}

