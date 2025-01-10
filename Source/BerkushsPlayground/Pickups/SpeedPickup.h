// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "SpeedPickup.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API ASpeedPickup : public APickup
{
	GENERATED_BODY()

public:

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere)
	float BaseSpeedBuff = 1000.f;
	UPROPERTY(EditAnywhere)
	float CrouchSpeedBuff = 650.f;
	UPROPERTY(EditAnywhere)
	float SpeedBuffTime = 10.f;
};