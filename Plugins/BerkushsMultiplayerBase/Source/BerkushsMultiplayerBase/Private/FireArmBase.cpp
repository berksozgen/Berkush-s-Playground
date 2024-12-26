// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "FireArmBase.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AFireArmBase::AFireArmBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	GunSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Body"));
	GunSkeletalMesh->SetupAttachment(RootComponent);
	GunSkeletalMesh->SetSkeletalMesh(WeaponInfo.WeaponMesh);

	MagazineSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Magazine"));
	MagazineSkeletalMesh->SetupAttachment(GunSkeletalMesh);
	MagazineSkeletalMesh->SetSkeletalMesh(WeaponInfo.MagazineMesh);
}

// Called when the game starts or when spawned
void AFireArmBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireArmBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireArmBase::StartShooting()
{
	bIsCurrentlyShooting = true;
	GetWorldTimerManager().SetTimer(
	FShootingHandler,
	this,
	&AFireArmBase::ShootingHandler,
	WeaponInfo.ShootingWaitTime,
	true
	);
}

void AFireArmBase::StopShooting()
{
	bIsCurrentlyShooting = false;
	GetWorldTimerManager().ClearTimer(FShootingHandler);
}

void AFireArmBase::ShootingHandler()
{
	if(MagazineAmmo >= 1)
	{
		//Spawn Emitter
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponInfo.FireEffect, GetActorLocation());/*Change this with muzzle location*/
		//Spawn sound
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), WeaponInfo.FireSound, GetActorLocation());/*Change this with muzzle location*/
		Server_Shooting();
	}
}

void AFireArmBase::Server_Shooting_Implementation()
{
	if(MagazineAmmo >= 1)
	{
		MagazineAmmo--;
		FHitResult Hit;
		//Raycast
		//Deal damage etc
		Multicast_Shooting(Hit);
	}
	else
	{
		StopShooting();
	}
}

bool AFireArmBase::Server_Shooting_Validate()
{
	return true;
	//return MagazineAmmo >= 1; //sorjoru bitince adam banlancak baba olmaz
}

void AFireArmBase::Multicast_Shooting_Implementation(const FHitResult& Hit)
{
	if(GetLocalRole()!=ROLE_AutonomousProxy)
	{
		//Spawn Emitter
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponInfo.FireEffect, GetActorLocation());/*Change this with muzzle location*/
		//Spawn sound
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), WeaponInfo.FireSound, GetActorLocation());/*Change this with muzzle location*/
	}

	if(true) //check hit resit
	{
		//Spawn Emitter
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponInfo.HitEffect, GetActorLocation());/*Change this with hit result location*/
		//Spawn sound
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), WeaponInfo.HitSound, GetActorLocation());/*Change this with with hit result location*/
	}
}
