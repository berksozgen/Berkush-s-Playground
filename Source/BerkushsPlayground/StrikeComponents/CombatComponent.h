// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "BerkushsPlayground/HUD/StrikeHUD.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

#define TRACE_LENGHT 80'000.f

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BERKUSHSPLAYGROUND_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	friend class AStrikeCharacter; //Tum degerlere (Protected ve Private ulasabiliyorz boyle)
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	void EquipWeapon(class AWeapon* WeaponToEquip);

protected:
	virtual void BeginPlay() override;
	void SetAiming(bool bIsAiming);

	UFUNCTION(Server, Reliable)
	void Server_SetAiming(bool bIsAiming);

	UFUNCTION()
	void OnRep_EquippedWeapon();

	void Fire();
	void FireButtonPressed(bool bPressed);
	UFUNCTION(Server, Reliable)
	void Server_Fire(const FVector_NetQuantize& TraceHitTarget); //Bu da 20 Bit'e indiriyor FVectoru :D
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Fire(const FVector_NetQuantize& TraceHitTarget);

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	void SetHUDCrosshairs(float DeltaTime);

private:
	UPROPERTY()
	class AStrikeCharacter* Character;
	UPROPERTY()
	class AStrikePlayerController* Controller;
	UPROPERTY()
	class AStrikeHUD* HUD;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon) //Anim Instance buna erisebilsin diye, Her Client anim instancelari kendi uzerinde cagiriyor.
	class AWeapon* EquippedWeapon;
	UPROPERTY(Replicated) //Anim Instance buna erisebilsin diye, Her Client anim instancelari kendi uzerinde cagiriyor.
	bool bAiming;
	
	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed;
	UPROPERTY(EditAnywhere)
	float AimWalkSpeed;

	bool bFireButtonPressed;

	/*
	 * HUD and Crosshairs
	 */
	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
	float CrosshairAimFactor;
	float CrosshairShootingFactor;

	FHudPackage HUDPackage;

	//
	FVector HitTarget;

	//
	//Aiming And FOV
	//

	//Field of view when not aiming; set to the camera's base FOV in BeginPlay
	float DefaultFOV;
	float CurrentFOV;
	UPROPERTY(EditAnywhere, Category = Combat)
	float ZoomedFOV = 30.f;
	UPROPERTY(EditAnywhere, Category = Combat)
	float ZoomInterpSpeed = 20.f;

	void InterpFOV(float DeltaTime);

	//
	//Automatic fire
	//
	FTimerHandle FireTimer;
	bool bCanFire = true;
	
	void StartFireTimer();
	void FireTimerFinished();
public:	
	
};