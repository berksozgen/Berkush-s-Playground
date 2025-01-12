// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "BerkushsPlayground/HUD/StrikeHUD.h"
#include "Components/ActorComponent.h"
#include "BerkushsPlayground/Weapon/WeaponTypes.h"
#include "BerkushsPlayground/StrikeTypes/CombatState.h"
#include "CombatComponent.generated.h"

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
	void SwapWeapons();
	void Reload();
	UFUNCTION(BlueprintCallable)
	void FinishReloading();
	
	void FireButtonPressed(bool bPressed);

	UFUNCTION(BlueprintCallable)
	void ShotgunShellReload();

	void JumpToShotgunEnd();

	UFUNCTION(BlueprintCallable)
	void ThrowGrenadeFinished();
	UFUNCTION(BlueprintCallable)
	void LaunchGrenade();
	UFUNCTION(Server, Reliable)
	void Server_LaunchGrenade(const FVector_NetQuantize& Target);

	void PickupAmmo(EWeaponType WeaponType, int32 AmmoAmount);
protected:
	virtual void BeginPlay() override;
	void SetAiming(bool bIsAiming);

	UFUNCTION(Server, Reliable)
	void Server_SetAiming(bool bIsAiming);

	UFUNCTION()
	void OnRep_EquippedWeapon();
	UFUNCTION()
	void OnRep_SecondaryWeapon();

	void Fire();
	//Burasi void FireButtonPressed(bool bPressed); fonksiyonun onceki yeri, durama gore geri almaya bakacam, mantikli gelmiyor publice tasimak sirf cooldownda millet taramasin yapmak
	UFUNCTION(Server, Reliable)
	void Server_Fire(const FVector_NetQuantize& TraceHitTarget); //Bu da 20 Bit'e indiriyor FVectoru :D
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Fire(const FVector_NetQuantize& TraceHitTarget);

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);

	void SetHUDCrosshairs(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void Server_Reload();

	void HandleReload();
	int32 AmountToReload();

	void ThrowGrenade();
	UFUNCTION(Server, Reliable)
	void Server_ThrowGrenade();
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> GrenadeClass;

	void DropEquippedWeapon();
	void AttachActorToRightHand(AActor* ActorToAttach);
	void AttachActorToLeftHand(AActor* ActorToAttach);
	void AttachActorToBackpack(AActor* ActorToAttach);
	void UpdateCarriedAmmo();
	void PlayEquipWeaponSound(AWeapon* WeaponToEquip);
	void ReloadEmptyWeapon();
	void ShowAttachedGrenade(bool bShowGrenade);
	void EquipPrimaryWeapon(AWeapon* WeaponToEquip);
	void EquipSecondaryWeapon(AWeapon* WeaponToEquip);

private:
	UPROPERTY()
	class AStrikeCharacter* Character;
	UPROPERTY()
	class AStrikePlayerController* Controller;
	UPROPERTY()
	class AStrikeHUD* HUD;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon) //Anim Instance buna erisebilsin diye, Her Client anim instancelari kendi uzerinde cagiriyor.
	class AWeapon* EquippedWeapon;
	UPROPERTY(ReplicatedUsing = OnRep_SecondaryWeapon)
	AWeapon* SecondaryWeapon;
	
	UPROPERTY(Replicated) //Anim Instance buna erisebilsin diye, Her Client anim instancelari kendi uzerinde cagiriyor.
	bool bAiming;
	
	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed;
	UPROPERTY(EditAnywhere)
	float AimWalkSpeed;

	bool bFireButtonPressed;
	
	//HUD and Crosshairs
	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
	float CrosshairAimFactor;
	float CrosshairShootingFactor;

	FHudPackage HUDPackage;

	//
	FVector HitTarget;

	//Aiming And FOV
	//Field of view when not aiming; set to the camera's base FOV in BeginPlay
	float DefaultFOV;
	float CurrentFOV;
	UPROPERTY(EditAnywhere, Category = Combat)
	float ZoomedFOV = 30.f;
	UPROPERTY(EditAnywhere, Category = Combat)
	float ZoomInterpSpeed = 20.f;

	void InterpFOV(float DeltaTime);
	
	//Automatic fire
	FTimerHandle FireTimer;
	bool bCanFire = true;
	
	void StartFireTimer();
	void FireTimerFinished();

	bool CanFire();

	//Carried ammo for the currently-equipped weapon
	UPROPERTY(ReplicatedUsing = OnRep_CarriedAmmo)
	int32 CarriedAmmo;
	UFUNCTION()
	void OnRep_CarriedAmmo();

	TMap<EWeaponType, int32> CarriedAmmoMap; /*Bu replike olmuyormus*/ //bi ara max carried ammo mapi yapayim

	UPROPERTY(EditAnywhere)
	int32 StartingAssaultRifleAmmo = 60;
	UPROPERTY(EditAnywhere)
	int32 StartingRocketAmmo = 1;
	UPROPERTY(EditAnywhere)
	int32 StartingPistolAmmo = 30;
	UPROPERTY(EditAnywhere)
	int32 StartingSubMachineGunAmmo = 40;
	UPROPERTY(EditAnywhere)
	int32 StartingShotgunAmmo = 10;
	UPROPERTY(EditAnywhere)
	int32 StartingSniperRifleAmmo = 10;
	UPROPERTY(EditAnywhere)
	int32 StartingGrenadeLauncherAmmo = 5;
	
	void InitializeCarriedAmmo();

	UPROPERTY(ReplicatedUsing = OnRep_CombatState)
	ECombatState CombatState = ECombatState::ECS_Unoccupied;
	UFUNCTION()
	void OnRep_CombatState();

	void UpdateAmmoValues();
	void UpdateShotgunAmmoValues();

	UPROPERTY(ReplicatedUsing = OnRep_GrenadeCount)
	int32 GrenadeCount = 2;
	UFUNCTION()
	void OnRep_GrenadeCount();
	UPROPERTY(EditAnywhere)
	int32 MaxGrenadeCount = 4;

	void UpdateHUDGrenades();

	void UpdateWeaponAmmoTypeText(EWeaponType WeaponType);
public:	
	FORCEINLINE int32 GetGrenadesCount() const { return GrenadeCount; }
	bool ShouldSwapWeapons();
};