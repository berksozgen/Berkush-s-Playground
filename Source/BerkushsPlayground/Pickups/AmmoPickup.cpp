// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "AmmoPickup.h"

#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "BerkushsPlayground/StrikeComponents/CombatComponent.h"

void AAmmoPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(OtherActor);
	if (StrikeCharacter)
	{
		UCombatComponent* Combat = StrikeCharacter->GetCombat();
		if (Combat)
		{
			Combat->PickupAmmo(WeaponType, AmmoAmount);
			Destroy();
		}
	}
	//Destroy(); //bunu if icine almamiz gerekmioyor mu//ben aliyom valla
}
