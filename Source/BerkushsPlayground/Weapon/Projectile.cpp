// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "Projectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "BerkushsPlayground/BerkushsPlayground.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true; //Bunu replike etmezsek, Tracer clientlerde gozukmuyor, sadece serverde spawnoluyor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECC_SkeletalMesh, ECollisionResponse::ECR_Block);
/*
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent")); //We don't need to attach this
	ProjectileMovementComponent->bRotationFollowsVelocity = true; //bu da eger yercekimi eklersek, ekledigi force'un yonunu yercekimiyle orantili yapiyor
*/ //Bunlari da kapama nedenimiz her projectilein kendi movement componentini olusturmasi saglamak
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (Tracer)
	{
		TracerComponent = UGameplayStatics::SpawnEmitterAttached(
			Tracer,
			CollisionBox,
			FName(/*Skeletal Meshimiz varsa bone name girebiliyoruz*/),
			GetActorLocation(),
			GetActorRotation(),
			EAttachLocation::KeepWorldPosition);
	}

	if (HasAuthority())
	{
		CollisionBox->OnComponentHit.AddDynamic(this, &AProjectile::OnHit); //Sadece serverde olussun istiyoruz bunun
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

void AProjectile::SpawnTrailSystem()
{
	if (TrailSystem)
	{
		TrailSystemComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			TrailSystem,
			GetRootComponent(),
			FName(),
			GetActorLocation(),
			GetActorRotation(),
			EAttachLocation::KeepWorldPosition,
			false);
	}
}

void AProjectile::ExplodeDamage()
{
	APawn* FiringPawn = GetInstigator();
	if (FiringPawn && HasAuthority())
	{
		AController* FiringController = FiringPawn->GetController();
		if (FiringController)
		{
			UGameplayStatics::ApplyRadialDamageWithFalloff(
				this, //World Context Object
				Damage, //Base Damage
				10.f, //Minimum Damage
				GetActorLocation(), //Origin
				DamageInnerRadius, //Damage Inner Radius
				DamageOuterRadius, //Damage Outer Radios
				1.f, //Damage Falloff (Ustlu sayilar iste 1 verince linear oluyo)
				UDamageType::StaticClass(), //Damage Type Class
				TArray<AActor*>(), //Ignore actors
				this, //Damage Causer
				FiringController); //Instigator (Gerek yok aslinda)
		}
	}
}

void AProjectile::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AProjectile::StartDestroyTimer()
{
	GetWorldTimerManager().SetTimer(
	DestroyTimer,
	this,
	&AProjectile::DestroyTimerFinished,
	DestroyTime);
}

void AProjectile::DestroyTimerFinished()
{
	Destroy();
}

void AProjectile::Destroyed() //Bu aktor replike oldugu icin, destroy fdonksiyonu kendiliginden  multicast, override ederek particle system icin ayri RPC acmaya gerek duymuyoruz
{
	if (ImpactParticles) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, GetActorTransform());
	if (ImpactSound) UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	Super::Destroyed();
}
