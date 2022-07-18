// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Components/InputComponent.h"
#include "ProjectileActor.h"


// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	MoveSpeed = 1000.0f;
	MaxHealth = 1000.0f;
	CurrentHealth = MaxHealth;
	MaxArmour = 1000.0f;
	CurrentArmour = MaxArmour;

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &AEnemyPawn::OnHit);

	
}

void AEnemyPawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		AProjectileActor* Proj = Cast<AProjectileActor>(OtherActor);

		if (Proj)
		{
			DamageEnemy(Proj->DamageAmount);
		}
	}
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

}

void AEnemyPawn::DamageEnemy(int InDmg, bool IsArmourPiercing)
{
	//Universal Enemy Damage Logic

	if (!IsArmourPiercing)//Damage is not armour piercing
	{
		//Check current armour count
		if (CurrentArmour >= InDmg)
			CurrentArmour -= InDmg;//If armour is above damage amount, reduce armour by that amount
		else
		{
			//If armour is less than damage recieved
			//Calculate how much damage is applied to health once armour is depleted
			int Damage = InDmg;
			Damage -= CurrentArmour;
			CurrentArmour = 0;
			CurrentHealth -= Damage;
		}
	}
	else
	{
		//If armour piercing damage, directly reduce health, ignoring armour
		CurrentHealth -= InDmg;
	}

	//If killing blow, destroy enemy
	if (CurrentHealth <= 0)
		OnDestroyEnemy();
}

void AEnemyPawn::OnDestroyEnemy()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Enemy Destroyed"));
	////Play Audio of Weapon Firing
	//if (DeathSoundEvent != nullptr)
	//{
	//	FAkAudioDevice::Get()->PostEvent(DeathSoundEvent, this);
	//}
	Destroy();
}

