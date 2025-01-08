// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "HitScanWeapon.h"

#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

void AHitScanWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* InstigatorController = OwnerPawn->GetController();
	if (InstigatorController == nullptr) return; //adam alttaki iffe yazdi da ne gerek var

	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	if (MuzzleFlashSocket)
	{
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		FVector Start = SocketTransform.GetLocation();
		FVector End = Start + (HitTarget - Start) * 1.25f; //bunun matemetigi biraz karisik 138. Ders HitScanWeapons dersind eanlatiyor

		FHitResult FireHit;
		UWorld* World = GetWorld();
		if (World)
		{
			World->LineTraceSingleByChannel(
				FireHit,
				Start,
				End,
				ECollisionChannel::ECC_Visibility);

			if (FireHit.bBlockingHit)
			{
				AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(FireHit.GetActor());
				if (StrikeCharacter)
				{
					if (HasAuthority())
					{
						UGameplayStatics::ApplyDamage(
							StrikeCharacter,
							Damage,
							InstigatorController,
							this,
							UDamageType::StaticClass());
					}
				}
				if (ImpactParticles)
				{
					UGameplayStatics::SpawnEmitterAtLocation(
						World,
						ImpactParticles,
						FireHit.ImpactPoint,
						FireHit.ImpactNormal.Rotation());
				}
			}
		}
	}
}