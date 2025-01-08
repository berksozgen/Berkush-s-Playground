// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "ProjectileBullet.h"

#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectileBullet::AProjectileBullet()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent")); //We don't need to attach this
	ProjectileMovementComponent->bRotationFollowsVelocity = true; //bu da eger yercekimi eklersek, ekledigi force'un yonunu yercekimiyle orantili yapiyor
	ProjectileMovementComponent->SetIsReplicated(true); //Bu adam daha once Character movement gibi kendi hallediyor demisti anlamadim valla
}

void AProjectileBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner()); //Silahin owneri character, projectilein owneri o karakter diyye gidiyo gidiyo, bu owner casti safe btw
	if (OwnerCharacter)
	{
		AController* OwnerController = OwnerCharacter->GetController();
		if (OwnerController)
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerController, this, UDamageType::StaticClass()/*Custom damage sinifi da yapabiliyormus*/);
		}
	}
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit); //Gene Projectile'dan inherit almamiza ragmen superi cagiriyoruz
}