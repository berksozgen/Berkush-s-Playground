// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RocketMovementComponent.generated.h"

/**
 * Bu sinifi acma nedenimiz, rocket ateslindiginde bizim oyuncu ile collide olabiliyor, namluyu ileri tasiyabilirdik de bu daha havali
 */
UCLASS()
class BERKUSHSPLAYGROUND_API URocketMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

protected: //Bunlarla birlikte seken mermi falan da yapabiliriz arastirmak lazim
	virtual EHandleBlockingHitResult HandleBlockingHit(const FHitResult& Hit, float TimeTick, const FVector& MoveDelta, float& SubTickTimeRemaining) override;
	virtual void HandleImpact(const FHitResult& Hit, float TimeSlice, const FVector& MoveDelta) override;
};