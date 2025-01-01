// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "ProjectileWeapon.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Projectile.h"

void AProjectileWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget); //Kendi yarattigimiz fonksiyonlarilari da override ederken base class da calissin isyiyorsak superi cagiriyoruz, sacma geldi acikcasi AWeapon::Fire() beklerdim super yerine

	if (!HasAuthority()) return; //Weapon base classinda dedigim gibi, su an authority sadece serverde, replication false olsaydi bunu her client cagircakti

	APawn* InstigatorPawn = Cast<APawn>(GetOwner());

	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
	if (MuzzleFlashSocket)
	{
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		// From Muzzle flash socket to hit location from TraceUnderCrosshairs
		FVector ToTarget = HitTarget - SocketTransform.GetTranslation();
		FRotator TargetRotation = ToTarget.Rotation();
		if (ProjectileClass && InstigatorPawn)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = GetOwner(); //Weapon'un Ownerinin oyuncu alinca oyuncuya setliyoruz, Yani Projectilin owneri da oyuncu oluyor boyle yapinca
			SpawnParameters.Instigator = InstigatorPawn; //Eger bu aktor damage verecekse damage veren kim sorusu iste, unreal niye owneri kullanmiyor bilmiyorum
			UWorld* World = GetWorld();
			if (World)
			{
				World->SpawnActor<AProjectile>(
					ProjectileClass,
					SocketTransform.GetLocation(),
					TargetRotation,
					SpawnParameters);
			}
		}
	}
}