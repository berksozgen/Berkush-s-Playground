// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "SheepController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TMS_Player.generated.h"


UCLASS()
class BERKUSHS_TMSIMULATOR_API ATMS_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATMS_Player();

	/** Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "TMSimulator_Alpha")
	TArray<UParticleSystem*> Effects;

public:
	void Shoot();
	void Jump();
	E_TMS_Color BulletColor;
	void SetNextBulletColor();
	TSubclassOf<class ATMS_Bullet> BulletClass;

	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "TMSimulator_Alpha")
	USceneComponent* HeadLevel;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "TMSimulator_Alpha")
	USceneComponent* GunHole;

	bool bCanFire {true};
	int32 BulletsFired {0};

	FTimerHandle FireHandle;
	void ResetCanFire();

};
