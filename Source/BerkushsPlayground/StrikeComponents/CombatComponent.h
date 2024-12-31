// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

protected:
	virtual void BeginPlay() override;
	void SetAiming(bool bIsAiming);

	UFUNCTION(Server, Reliable)
	void Server_SetAiming(bool bIsAiming);

	UFUNCTION()
	void OnRep_EquippedWeapon();

private:
	class AStrikeCharacter* Character;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon) //Anim Instance buna erisebilsin diye, Her Client anim instancelari kendi uzerinde cagiriyor.
	class AWeapon* EquippedWeapon;
	UPROPERTY(Replicated) //Anim Instance buna erisebilsin diye, Her Client anim instancelari kendi uzerinde cagiriyor.
	bool bAiming;

public:	
	
};
