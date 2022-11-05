// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickupActor.h"
#include "WeaponActor.h"

AWeaponPickupActor::AWeaponPickupActor()
{

}

void AWeaponPickupActor::PickupResponse(AHyperDrivePawn* Player)
{
	if (Player != nullptr)
	{
		if (NewWeapon != nullptr)
		{
			AWeaponActor* W = GetWorld()->SpawnActor<AWeaponActor>(NewWeapon, Player->GetActorLocation(), GetActorRotation());
			AttachToActor(Player,FAttachmentTransformRules::KeepWorldTransform);
			Player->WeaponInventory.Add(W);

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("New Weapon? Hell yeah!"));

			Destroy();

		}
	}
}
