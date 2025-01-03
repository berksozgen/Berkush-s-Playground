// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BerkushsPlayground/StrikeTypes/TurningInPlace.h"
#include "BerkushsPlayground/Interfaces/InteractWithCrosshairsInterface.h"
#include "Components/TimelineComponent.h"
#include "StrikeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class BERKUSHSPLAYGROUND_API AStrikeCharacter : public ACharacter, public IInteractWithCrosshairsInterface
{
	GENERATED_BODY()
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* StrikeMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Equip Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipAction;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;
	
	/** Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

public:
	AStrikeCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;

	void PlayFireMontage(bool bAiming);
	void PlayElimMontage();
	
	virtual void OnRep_ReplicatedMovement() override;

	void Elim();
	UFUNCTION(NetMulticast, Reliable) //Bunu multicast yapacagimiza OnRep'te can kontrolunu yapsak ne olurdu ki
	void Multicast_Elim();

	virtual void Destroyed() override;
	
	/** Called for movement input */
	void EnhancedMove(const FInputActionValue& Value);
	/** Called for looking input */
	void EnhancedLook(const FInputActionValue& Value);
	//
	void EquipPressed(const FInputActionValue& Value);
	//
	void CrouchPressed(const FInputActionValue& Value);
	//
	void AimPressed(const FInputActionValue& Value);
	void AimReleased(const FInputActionValue& Value);
	//
	void FirePressed(const FInputActionValue& Value);
	void FireReleased(const FInputActionValue& Value);
	
protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void AimOffset(float DeltaTime);
	void SimProxiesTurn();
	void CalculateAO_Pitch();

	virtual void Jump() override;
	
	void PlayHitReactMontage();
	
	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

	void UpdateHUDHealth();

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;
	
	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	class AWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon); //RepNotifylara sadece kendi turlerindeki seyi input param olarak verebiliyoruz

	UPROPERTY(VisibleAnywhere)
	class UCombatComponent* Combat;

	UFUNCTION(Server, Reliable)
	void Server_EquipButtonPressed();

	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = Combat)
	class UAnimMontage* FireWeaponMontage;
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* HitReactMontage;
	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* ElimMontage;
	
	void HideCameraIfCharacterClose(); //Bu isime cozum bul
	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

	bool bRotateRootBone;
	float TurnThreshold = .5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;
	float TimeSinceLastMovementReplication;

	float CalculateSpeed();

	class AStrikePlayerController* StrikePlayerController;

	//Player Health //Cani player state yerine buraya ekleme nedenimiz, PlayerState'den daha fazla net update aliyor olusumuz
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;
	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere, Category = "Player Stats")
	float Health = 100.f;
	UFUNCTION()
	void OnRep_Health();

	bool bElimmed = false;
	FTimerHandle ElimTimer;
	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;
	void ElimTimerFinished();

	//Dissolve Effect
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* DissolveTimeline;
	FOnTimelineFloat DissolveTrack;
	UPROPERTY(EditAnywhere)
	UCurveFloat* DissolveCurve;
	void StartDissolve();
	UFUNCTION()
	void UpdateDissolveMaterial(float DissolveValue);
	UPROPERTY(EditAnywhere, Category = Elim) //Material Instance set on the Blueprint, used with the dynamic material instance
	UMaterialInstance* DissolveMaterialInstance;
	UPROPERTY(VisibleAnywhere, Category = Elim) //Dynamic Instance that we can change at runtime
	UMaterialInstanceDynamic* DynamicDissolveMaterialInstance;

	//ElimBot
	UPROPERTY(EditAnywhere, Category = Elim)
	UParticleSystem* ElimBotEffect;
	UPROPERTY(VisibleAnywhere, Category = Elim)
	UParticleSystemComponent* ElimBotComponent;
	UPROPERTY(EditAnywhere, Category = Elim)
	class USoundCue* ElimBotSound;

public:	
	void SetOverlappingWeapon(AWeapon* Weapon);
	bool IsWeaponEquipped();
	bool IsAiming();
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
	class AWeapon* GetEquippedWeapon();
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }
	FORCEINLINE bool IsElimmed() const { return bElimmed; }
	
	FVector GetHitTarget() const;
};