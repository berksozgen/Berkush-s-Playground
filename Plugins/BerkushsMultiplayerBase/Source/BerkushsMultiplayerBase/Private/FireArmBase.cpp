// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "FireArmBase.h"

// Sets default values
AFireArmBase::AFireArmBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	GunSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Body"));
	GunSkeletalMesh->SetupAttachment(RootComponent);

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

void AFireArmBase::Shoot()
{
	
}

