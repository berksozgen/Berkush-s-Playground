// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "JumpPickup.h"

#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "BerkushsPlayground/StrikeComponents/BuffComponent.h"

void AJumpPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(OtherActor);
	if (StrikeCharacter)
	{
		UBuffComponent* Buff = StrikeCharacter->GetBuff();
		if (Buff)
		{
			Buff->BuffJump(JumpZVelocityBuff, JumpBuffTime);
			Destroy();
		}
	}
}
