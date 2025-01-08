// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "ProjectileRocket.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraSystemInstanceController.h"
#include "RocketMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

AProjectileRocket::AProjectileRocket()
{
	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket Mesh"));
	RocketMesh->SetupAttachment(RootComponent);
	RocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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
				200.f, //Damage Inner Radius
				500.f, //Damage Outer Radios
				1.f, //Damage Falloff (Ustlu sayilar iste 1 verince linear oluyo)
				UDamageType::StaticClass(), //Damage Type Class
				TArray<AActor*>(), //Ignore actors
				this, //Damage Causer
				FiringController); //Instigator (Gerek yok aslinda)
		}
	}
	
	GetWorldTimerManager().SetTimer(
		DestroyTimer,
		this,
		&AProjectileRocket::DestroyTimerFinished,
		DestroyTime);
	
	if (ImpactParticles) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, GetActorTransform());
	if (ImpactSound) UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	if (RocketMesh) RocketMesh->SetVisibility(false);
	if (CollisionBox) CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (TrailSystemComponent && TrailSystemComponent->GetSystemInstanceController()) TrailSystemComponent->GetSystemInstanceController()->Deactivate(); //GetSystemInstance deprached olmus
	if (ProjectileLoopComponent && ProjectileLoopComponent->IsPlaying()) ProjectileLoopComponent->Stop();
}

void AProjectileRocket::DestroyTimerFinished()
{
	Destroy();
}

void AProjectileRocket::Destroyed()
{
	//Super::Destroyed(); //Bilerek null praktik
}