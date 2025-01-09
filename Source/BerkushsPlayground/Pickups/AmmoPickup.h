// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API AAmmoPickup : public APickup
{
	GENERATED_BODY()

public:

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override; //override ederken UFUNCTION makrosuna gerek yok

private:
	UPROPERTY(EditAnywhere)
	int32 AmmoAmount = 30;
	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;
};