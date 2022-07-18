#include "HyperDrivePawn.h"
#include "HyperDriveProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "WeaponActor.h"
#include "PickupActor.h"
#include "ResupplyPickupActor.h"

const FName AHyperDrivePawn::MoveForwardBinding("MoveForward");
const FName AHyperDrivePawn::MoveRightBinding("MoveRight");

AHyperDrivePawn::AHyperDrivePawn()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	//Default Values
	MaxHealth = MaxArmour = 1000;
	CurrentHealth = MaxHealth;
	CurrentArmour = 0;
	// Movement
	MoveSpeed = 1000.0f;

	//Input
	bIsFiring = false;
}

void AHyperDrivePawn::BeginPlay()
{
	Super::BeginPlay();

	ShipMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AHyperDrivePawn::OnOverlapBegin);
}

void AHyperDrivePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction("Fire_Primary", IE_Pressed, this, &AHyperDrivePawn::ActivateWeaponFiring);
	PlayerInputComponent->BindAction("Fire_Primary", IE_Released, this, &AHyperDrivePawn::DeactivateWeaponFiring);

}

void AHyperDrivePawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);
	const float TurnValue = GetInputAxisValue("Turn");
	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, GetActorRotation(), true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, GetActorRotation(), true);
		}
	}

	if (bIsFiring)
	{
		Fire();
	}

}

void AHyperDrivePawn::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		APickupActor* Pickup = Cast<APickupActor>(OtherActor);

		if (Pickup)
		{
			Pickup->PlayPickupSound();

			AResupplyPickupActor* Resupply = Cast<AResupplyPickupActor>(Pickup);

			if (Resupply)
			{
				if (Resupply->Type == EResupplyType::HEALTH)
				{
					CurrentHealth += Resupply->PickupValue;
					Resupply->Destroy();
				}

				if (Resupply->Type == EResupplyType::ARMOUR)
				{
					CurrentArmour += Resupply->PickupValue;
					Resupply->Destroy();
				}
			}
		}
	}
}

void AHyperDrivePawn::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AHyperDrivePawn::ActivateWeaponFiring()
{
	if (CurrentWeapon)
	{
		bIsFiring = true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No Weapon"));
	}
}

void AHyperDrivePawn::DeactivateWeaponFiring()
{
	bIsFiring = false;
}


void AHyperDrivePawn::Fire()
{
	if (CurrentWeapon)
	{
		// Spawn projectile in front of the player, offset slightly
		const FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 100.0f);
		CurrentWeapon->Fire(SpawnLocation, GetActorRotation());
	}
}
