// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "Pickup.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true; //Destroyed her clientte gelsin diye

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetSphereRadius(50.f);
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(OverlapSphere);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_PURPLE);
	PickupMesh->MarkRenderStateDirty(); //Renderer'in bunu tekrar renderlamasiini sagliyor kabaca
	if (PickupMesh) PickupMesh->SetRenderCustomDepth(true);
	
	PickupSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PickupSkeletalMesh"));
	PickupSkeletalMesh->SetupAttachment(OverlapSphere);
	PickupSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupSkeletalMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_PURPLE);
	PickupSkeletalMesh->MarkRenderStateDirty(); //Renderer'in bunu tekrar renderlamasiini sagliyor kabaca
	if (PickupSkeletalMesh) PickupSkeletalMesh->SetRenderCustomDepth(true);
	
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(
			BindOverlapTimer,
			this,
			&APickup::BindOverlapTimerFinished,
			BindOverlapTime);
	}
}

void APickup::BindOverlapTimerFinished() //Bunu beginplayde yapmama nedenimiz adamlar icinde bekleyip buga sokmasin diye, bug degil gerci
{
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnSphereOverlap);
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PickupMesh)
	{
		PickupMesh->AddLocalRotation(FRotator(0.f, BaseTurnRate * DeltaTime, 0.f));
	}
	if (PickupSkeletalMesh)
	{
		PickupSkeletalMesh->AddLocalRotation(FRotator(0.f, BaseTurnRate * DeltaTime, 0.f));
	}
}

void APickup::Destroyed()
{
	Super::Destroyed();

	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}
}

void APickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

