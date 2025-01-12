// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BerkushsPlayground/Weapon/WeaponTypes.h"

#include "Pickup.generated.h"

UCLASS()
class BERKUSHSPLAYGROUND_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup();
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	float BaseTurnRate = 45.f;

private:
	UPROPERTY(EditAnywhere)
	class USphereComponent* OverlapSphere;

	UPROPERTY(EditAnywhere)
	class USoundCue* PickupSound;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* PickupMesh;
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* PickupSkeletalMesh;

	FTimerHandle BindOverlapTimer;
	UPROPERTY(EditAnywhere)
	float BindOverlapTime = .15f;
	void BindOverlapTimerFinished();
public:	
	
};