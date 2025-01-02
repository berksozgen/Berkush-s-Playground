// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "ProjectileBullet.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

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