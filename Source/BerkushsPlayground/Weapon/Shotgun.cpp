// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "Shotgun.h"

#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void AShotgun::Fire(const FVector& HitTarget)
{
	AWeapon::Fire(HitTarget); //Super yazinca HitScan weaponun fire i gelecekti, boyle yapinca en base sinifi geldi
	
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* InstigatorController = OwnerPawn->GetController();

	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if (MuzzleFlashSocket)
	{
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		FVector Start = SocketTransform.GetLocation();

		TMap<AStrikeCharacter*, uint32> HitMap;
		for (uint32 i = 0; i < NumberOfPellets; i++)
		{
			FHitResult FireHit;
			WeaponTraceHit(Start, HitTarget, FireHit);

			AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(FireHit.GetActor());
			if (StrikeCharacter && HasAuthority() && InstigatorController) //bu if duzenlenebilir
			{
				if (HitMap.Contains(StrikeCharacter)) HitMap[StrikeCharacter]++;
				else HitMap.Emplace(StrikeCharacter, 1);
			}
			
			if (ImpactParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(
					GetWorld(),
					ImpactParticles,
					FireHit.ImpactPoint,
					FireHit.ImpactNormal.Rotation());
			}
			if (HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(
					this,
					HitSound,
					FireHit.ImpactPoint,
					.5f,
					FMath::FRandRange(-.5f, .5f));
			}
		}

		for (auto HitPair : HitMap)
		{
			if (InstigatorController)
			{
				if (HitPair.Key && HasAuthority() && InstigatorController)
				{
					UGameplayStatics::ApplyDamage(
						HitPair.Key,
						Damage * HitPair.Value,
						InstigatorController,
						this,
						UDamageType::StaticClass());
				}
			}
		}
	}	
}
