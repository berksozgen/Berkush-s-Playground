// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "ProjectileRocket.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraSystemInstanceController.h"
#include "RocketMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

AProjectileRocket::AProjectileRocket()
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RocketMovementComponent = CreateDefaultSubobject<URocketMovementComponent>(TEXT("RocketMovementComponent")); //Custom  movement component espirisi yok pek
	RocketMovementComponent->bRotationFollowsVelocity = true; //bunu false yapmicak miydik
	RocketMovementComponent->SetIsReplicated(true);
}

void AProjectileRocket::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority()) //clientlerde de meshi kapatmak icin
	{
		CollisionBox->OnComponentHit.AddDynamic(this, &AProjectileRocket::OnHit); //Sadece serverde olussun istiyoruz bunun
	}

	SpawnTrailSystem();

	if (ProjectileLoop && LoopingSoundAttenuation)
	{
		ProjectileLoopComponent = UGameplayStatics::SpawnSoundAttached(
			ProjectileLoop,
			GetRootComponent(),
			FName(),
			GetActorLocation(),
			EAttachLocation::KeepWorldPosition,
			false,
			1.f,
			1.f,
			0.f,
			LoopingSoundAttenuation,
			(USoundConcurrency*)nullptr, //C type cast ile null ptr veriyoruz
			false);
	}
}

void AProjectileRocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == GetOwner()) return; //Kendine vurunca patlamasin diye gene hasar aliyoruz da kendine vurunca patlamasi sacmaydi ondan
	
	ExplodeDamage();
	
	StartDestroyTimer();
	
	if (ImpactParticles) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, GetActorTransform());
	if (ImpactSound) UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	if (ProjectileMesh) ProjectileMesh->SetVisibility(false);
	if (CollisionBox) CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (TrailSystemComponent && TrailSystemComponent->GetSystemInstanceController()) TrailSystemComponent->GetSystemInstanceController()->Deactivate(); //GetSystemInstance deprached olmus
	if (ProjectileLoopComponent && ProjectileLoopComponent->IsPlaying()) ProjectileLoopComponent->Stop();
}



void AProjectileRocket::Destroyed()
{
	//Super::Destroyed(); //Bilerek null praktik
}