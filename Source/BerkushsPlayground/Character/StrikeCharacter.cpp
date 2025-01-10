// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "StrikeCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BerkushsPlayground/StrikeComponents/CombatComponent.h"
#include "BerkushsPlayground/StrikeComponents/BuffComponent.h"
#include "BerkushsPlayground/Weapon/Weapon.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "StrikeAnimInstance.h"
#include "BerkushsPlayground/BerkushsPlayground.h"
#include "BerkushsPlayground/Door/Door.h"
#include "BerkushsPlayground/PlayerController/StrikePlayerController.h"
#include "BerkushsPlayground/GameMode/StrikeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "BerkushsPlayground/PlayerState/StrikePlayerState.h"
#include "BerkushsPlayground/Weapon/WeaponTypes.h"

#pragma region UnrealDefaultFunc
AStrikeCharacter::AStrikeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; /*bunu sade bp ile yapti adam ama burda bana not olarak kalsin*/
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);

	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	Combat->SetIsReplicated(true);

	Buff = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));
	Buff->SetIsReplicated(true);

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	//Fix camera, birileri araya gecince zoom yapmasin diye
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 850.f);

	TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	//Eleman shooter game icin bu degerler iyi dedi bakalim artik orjinali 100 e 3 mu neydi btw project settingsten serverin tickini arttircam
	NetUpdateFrequency = 66.f;
	MinNetUpdateFrequency = 33.f;
	//Line trace atmak icin
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	//Projectile Capsulu degil meshi kullansin diye
	GetMesh()->SetCollisionObjectType(ECC_SkeletalMesh);

	DissolveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DissolveTimelineComponent"));

	AttachedGrenade = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Attached Grenade"));
	AttachedGrenade->SetupAttachment(GetMesh(), FName(TEXT("GrenadeSocket")));
	AttachedGrenade->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AStrikeCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AStrikeCharacter, OverlappingWeapon, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AStrikeCharacter, OverlappingDoor, COND_OwnerOnly);
	//DOREPLIFETIME(AStrikeCharacter, OverlappingWeapon); //Boyle yapinca biri silah ustunde durunca herkeste gozukuyor
	DOREPLIFETIME(AStrikeCharacter, Health);
	DOREPLIFETIME(AStrikeCharacter, Shield);
	//DOREPLIFETIME(AStrikeCharacter, bIsCurrentlyAlive); //bu da deneme
	DOREPLIFETIME(AStrikeCharacter, bDisableGameplay);
}

void AStrikeCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (Combat) Combat->Character = this;
	if (Buff)
	{
		Buff->Character = this;
		Buff->SetInitialSpeeds(GetCharacterMovement()->MaxWalkSpeed, GetCharacterMovement()->MaxWalkSpeedCrouched);
		Buff->SetInitialJumpVelocity(GetCharacterMovement()->JumpZVelocity);
	}
}

void AStrikeCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultWeapon();
	UpdateHUDAmmo();
	UpdateHUDHealth();
	UpdateHUDShield();
	if (StrikePlayerController)	StrikePlayerController->SetHUDKilledText(FString(""));
	
	if (HasAuthority())
	{
		OnTakeAnyDamage.AddDynamic(this, &AStrikeCharacter::ReceiveDamage);
	}
	if (AttachedGrenade)
	{
		AttachedGrenade->SetVisibility(false);
	}
}

void AStrikeCharacter::Destroyed()
{
	Super::Destroyed();
	
	if (ElimBotComponent) ElimBotComponent->DestroyComponent();
	//evet hatasini anladi, gamemodu cagiriyor burda, inprogressde degilse ona gore cekiyor, dunyanin en salakca isi bence btw
	//if (Combat && Combat->EquippedWeapon) // bunu da disable input olan sectionda yapti anlamadim valla olunce silah destroy olursa komik olur //komik olmuyormus bu adamin eklicegi vari skm
	//{
		//Combat->EquippedWeapon->Destroy();
	//}
}

void AStrikeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateInPlace(DeltaTime);
	HideCameraIfCharacterClose();
	PollInit(); //Dedigim gibi buna yer bulmak lazim
}

#pragma endregion UnrealDefaultFunc

void AStrikeCharacter::RotateInPlace(float DeltaTime) //buna da baska yer bulmak lazim
{
	if (bDisableGameplay) //buraya da bu sacma
	{
		bUseControllerRotationYaw = false;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
		return; 
	}

	if (GetLocalRole() > ENetRole::ROLE_SimulatedProxy && IsLocallyControlled()) //Enum oldugu icin yapabiliyorz, none, sim, autonumus, authority diye gidiyo
	{
		AimOffset(DeltaTime);
	}
	else
	{
		TimeSinceLastMovementReplication += DeltaTime;
		if (TimeSinceLastMovementReplication > .25f) OnRep_ReplicatedMovement();
		CalculateAO_Pitch();
	}
}

#pragma region Animations
void AStrikeCharacter::PlayFireMontage(bool bAiming)
{
	if (Combat == nullptr || Combat->EquippedWeapon == nullptr) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && FireWeaponMontage)
	{
		AnimInstance->Montage_Play(FireWeaponMontage);
		FName SectionName;
		SectionName = bAiming ? FName("RifleAim") : FName("RifleHip");
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

void AStrikeCharacter::PlayReloadMontage()
{
	if (Combat == nullptr || Combat->EquippedWeapon == nullptr) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ReloadMontage)
	{
		AnimInstance->Montage_Play(ReloadMontage);
		FName SectionName;

		switch (Combat->EquippedWeapon->GetWeaponType())
		{
		case EWeaponType::EWT_AssaultRifle:
			SectionName = FName("Rifle");
			break;
		case EWeaponType::EWT_RocketLauncher:
			SectionName = FName("RocketLauncher");
			break;
		case EWeaponType::EWT_Pistol:
			SectionName = FName("Pistol");
			break;
		case EWeaponType::EWT_SubMachineGun:
			SectionName = FName("Pistol"); //bu animimiz yok he smg icin ama fixlemicez sonra gibi
			break;
		case EWeaponType::EWT_Shotgun:
			SectionName = FName("Shotgun");
			break;
		case EWeaponType::EWT_SniperRifle:
			SectionName = FName("SniperRifle");
			break;
		case EWeaponType::EWT_GrenadeLauncher:
			SectionName = FName("GrenadeLauncher"); //bunun custom animasyonu yok aslinda ama sesler farkli
			break;
		}
		
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

void AStrikeCharacter::PlayElimMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ElimMontage) AnimInstance->Montage_Play(ElimMontage);
}

void AStrikeCharacter::PlayThrowGrenadeMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ThrowGrenadeMontage) AnimInstance->Montage_Play(ThrowGrenadeMontage);
}

void AStrikeCharacter::PlayHitReactMontage()
{
	if (Combat == nullptr || Combat->EquippedWeapon == nullptr) return; //Silahimiz yokken garip duruyor

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HitReactMontage)
	{
		AnimInstance->Montage_Play(HitReactMontage);
		FName SectionName("FromFront");
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}
#pragma endregion Animations

#pragma region JustOwner
void AStrikeCharacter::HideCameraIfCharacterClose() //Buraya hafif refactor gerekecek, if blogu yerine lokal boolda saklayim
{
	if (!IsLocallyControlled()) return;
	if ((FollowCamera->GetComponentLocation() - GetActorLocation()).Size() < CameraThreshold)
	{
		GetMesh()->SetVisibility(false);
		if (Combat && Combat->EquippedWeapon && Combat->EquippedWeapon->GetWeaponMesh())
		{
			Combat->EquippedWeapon->GetWeaponMesh()->bOwnerNoSee = true;
		}
	}
	else
	{
		GetMesh()->SetVisibility(true);
		if (Combat && Combat->EquippedWeapon && Combat->EquippedWeapon->GetWeaponMesh())
		{
			Combat->EquippedWeapon->GetWeaponMesh()->bOwnerNoSee = false;
		}
	}
}

void AStrikeCharacter::AimOffset(float DeltaTime)
{
	if(Combat && Combat->EquippedWeapon == nullptr) return;
	
	float Speed = CalculateSpeed();
	bool bIsInAir = GetCharacterMovement()->IsFalling();

	if (Speed == 0.f && !bIsInAir) //standing still, not jumping
	{
		bRotateRootBone = true;
		FRotator CurrentAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation); //sonucu -1 ile carpmak yerine ters cevirdim hehe
		AO_Yaw = DeltaAimRotation.Yaw;
		if (TurningInPlace == ETurningInPlace::ETIP_NotTurning)
		{
			InterpAO_Yaw = AO_Yaw;
		}
		bUseControllerRotationYaw = true;
		TurnInPlace(DeltaTime);
	}
	if (Speed > 0.f || bIsInAir) //running or jumping
	{
		bRotateRootBone = false;
		StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		AO_Yaw = 0.f;
		bUseControllerRotationYaw = true;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	}
	CalculateAO_Pitch();
}
#pragma endregion JustOwner

void AStrikeCharacter::UpdateHUDHealth() //Bunu owner onlye alayim bi ara
{
	StrikePlayerController = StrikePlayerController == nullptr ? Cast<AStrikePlayerController>(GetController()) : StrikePlayerController;
	if (StrikePlayerController)
	{
		StrikePlayerController->SetHUDHealth(Health, MaxHealth);
		if (Health <= 0.f) //En dogru yer burasi ddegil biliyom
		{
			StrikePlayerController->SetHUDKilledText(FString(TEXT("You Have Been Eliminated!")));
		}
	}
}

void AStrikeCharacter::UpdateHUDShield()
{
	StrikePlayerController = StrikePlayerController == nullptr ? Cast<AStrikePlayerController>(GetController()) : StrikePlayerController;
	if (StrikePlayerController)
	{
		StrikePlayerController->SetHUDShield(Shield, MaxShield);
	}
}

void AStrikeCharacter::UpdateHUDAmmo()
{
	StrikePlayerController = StrikePlayerController == nullptr ? Cast<AStrikePlayerController>(GetController()) : StrikePlayerController;
	if (StrikePlayerController && Combat && Combat->EquippedWeapon)
	{
		StrikePlayerController->SetHUDCarriedAmmo(Combat->CarriedAmmo);
		StrikePlayerController->SetHUDWeaponAmmo(Combat->EquippedWeapon->GetAmmo());
	}
}

void AStrikeCharacter::CalculateAO_Pitch()
{
	AO_Pitch = GetBaseAimRotation().Pitch; //Serverde rotasyon 0 360 arasinda gidiyor, Unrealin bok yemesi, //5 bayta dusuruyor
	if(AO_Pitch > 90.f && !IsLocallyControlled()) //Niye IsLocally conterolled diyip -180.f cikarmadik onu anlamadim; bir ara test ederim
	{
		// map pitch from [270, 360) to [-90, 0)
		FVector2D InRange(270.f, 360.f);
		FVector2D OutRange(-90.f, 0.f);
		AO_Pitch = FMath::GetMappedRangeValueClamped(InRange,OutRange, AO_Pitch);
	}
}

void AStrikeCharacter::TurnInPlace(float DeltaTime)
{
	if (AO_Yaw > 90.f) TurningInPlace = ETurningInPlace::ETIP_Right;
	else if (AO_Yaw < -90.f) TurningInPlace = ETurningInPlace::ETIP_Left;
	
	if (TurningInPlace != ETurningInPlace::ETIP_NotTurning)
	{
		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 4.f);
		AO_Yaw = InterpAO_Yaw;
		if (FMath::Abs(AO_Yaw) < 15.f)
		{
			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		}
	}
}
float AStrikeCharacter::CalculateSpeed()
{
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.f;
	return Velocity.Size();
}

#pragma region Input
void AStrikeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(StrikeMappingContext, 0);
		}
	}
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AStrikeCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStrikeCharacter::EnhancedMove);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStrikeCharacter::EnhancedLook);
		// Equipping
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &AStrikeCharacter::EquipPressed);
		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AStrikeCharacter::InteractPressed);
		// Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AStrikeCharacter::CrouchPressed);
		// Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AStrikeCharacter::AimPressed);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AStrikeCharacter::AimReleased);
		// Firing
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AStrikeCharacter::FirePressed);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AStrikeCharacter::FireReleased);
		//Reloading
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AStrikeCharacter::ReloadPressed);
		//Throwing Grenade
		EnhancedInputComponent->BindAction(ThrowGrenadeAction, ETriggerEvent::Started, this, &AStrikeCharacter::ThrowGrenadePressed);
	}
	else UE_LOG(LogTemp, Error, TEXT("Strike Karakteri EnhancedInputComponent'i Aktive Edemedi"));
}

void AStrikeCharacter::EnhancedMove(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	MoveForward(MovementVector.Y);
	MoveRight(MovementVector.X);
}

void AStrikeCharacter::EnhancedLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	Turn(LookAxisVector.X);
	LookUp(LookAxisVector.Y);
}

void AStrikeCharacter::Jump() { if (bDisableGameplay) return; /*icime sinmiyor bu*/ (bIsCrouched) ? UnCrouch() : Super::Jump(); }

void AStrikeCharacter::EquipPressed(const FInputActionValue& Value) //Parametrelere gerek var mi bilmiyorum, Enhanced input mal ama biraz
{
	if (bDisableGameplay) return; //icime sinmiyor bu
	if (Combat) Server_EquipButtonPressed();
}

void AStrikeCharacter::InteractPressed(const FInputActionValue& Value)
{
	if (bDisableGameplay) return;
	Server_InteractButtonPressed();
}

void AStrikeCharacter::CrouchPressed(const FInputActionValue& Value) { if (bDisableGameplay) return; /*icime sinmiyor bu*/ (bIsCrouched) ? UnCrouch() : Crouch(); }

void AStrikeCharacter::AimPressed(const FInputActionValue& Value) { if (bDisableGameplay) return; /*icime sinmiyor bu*/ if (Combat) Combat->SetAiming(true); }
void AStrikeCharacter::AimReleased(const FInputActionValue& Value) { if (bDisableGameplay) return; /*icime sinmiyor bu hele burda sacma geldi*/ if (Combat) Combat->SetAiming(false); }

void AStrikeCharacter::FirePressed(const FInputActionValue& Value) { if (bDisableGameplay) return; /*icime sinmiyor bu*/ if (Combat) Combat->FireButtonPressed(true); }
void AStrikeCharacter::FireReleased(const FInputActionValue& Value) { if (bDisableGameplay) return; /*icime sinmiyor bu*/ if (Combat) Combat->FireButtonPressed(false); }

void AStrikeCharacter::ReloadPressed(const FInputActionValue& Value) { if (bDisableGameplay) return; /*icime sinmiyor bu*/ if (Combat) Combat->Reload(); }

void AStrikeCharacter::ThrowGrenadePressed(const FInputActionValue& Value)
{
	if (Combat)
	{
		Combat->ThrowGrenade();
	}
}

void AStrikeCharacter::MoveForward(float Value)
{
	if (bDisableGameplay) return; //icime sinmiyor bu
	if(Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void AStrikeCharacter::MoveRight(float Value)
{
	if (bDisableGameplay) return; //icime sinmiyor bu
	if(Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void AStrikeCharacter::Turn(float Value) { AddControllerYawInput(Value); }
void AStrikeCharacter::LookUp(float Value) { AddControllerPitchInput(-Value); }
#pragma endregion Input

#pragma region NetworkEvents
void AStrikeCharacter::Server_EquipButtonPressed_Implementation()
{
	if (Combat)
	{
		if (OverlappingWeapon)
		{
			Combat->EquipWeapon(OverlappingWeapon);
		}
		else if (Combat->ShouldSwapWeapons())
		{
			Combat->SwapWeapons();
		}
	}
}

void AStrikeCharacter::Server_InteractButtonPressed_Implementation()
{
	if (OverlappingDoor) OverlappingDoor->InteractWithDoor();
	//Baska interactable ekleyince bunu interface e cekicem
}

void AStrikeCharacter::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	class AController* InstigatorController, AActor* DamageCauser) /*Network event mi emin degilim*/
{
	if (bElimmed) return; //bElimmed diye varimiz varmis la malim ben

	float DamageToHealth = Damage;
	if (Shield > 0.f)
	{
		if (Shield >= Damage)
		{
			Shield = FMath::Clamp(Shield - Damage, 0.0f, MaxShield);
			DamageToHealth = 0.f;
		}
		else
		{
			DamageToHealth = FMath::Clamp(DamageToHealth - Shield, 0.f, Damage);
			Shield = 0.f;
		}
	}
	
	Health = FMath::Clamp(Health - DamageToHealth, 0.0f, MaxHealth);
	
	UpdateHUDHealth(); //niye bunu ikisinde de cagiriyoruz, tamam repler serverde calismyor da owner degilse anlami ne
	UpdateHUDShield();
	PlayHitReactMontage();

	if (Health == 0.f)
	{
		//bIsCurrentlyAlive = false; //bu da denemenin devami
		AStrikeGameMode* StrikeGameMode = GetWorld()->GetAuthGameMode<AStrikeGameMode>();
		if (StrikeGameMode)
		{
			StrikePlayerController = StrikePlayerController == nullptr ? Cast<AStrikePlayerController>(Controller) : StrikePlayerController;
			AStrikePlayerController* AttackerController = Cast<AStrikePlayerController>(InstigatorController);
			StrikeGameMode->PlayerEliminated(this, StrikePlayerController, AttackerController); //nullcheck atmama nedenimiz gamemode da atcaz
		}
	}
}

void AStrikeCharacter::OnRep_Health(float LastHealth)
{
	UpdateHUDHealth();
	if (Health < LastHealth)
	{
		PlayHitReactMontage();
	}
}

void AStrikeCharacter::OnRep_Shield(float LastShield)
{
	UpdateHUDShield();
	if (Shield < LastShield)
	{
		PlayHitReactMontage();
	}
}

void AStrikeCharacter::SetOverlappingWeapon(AWeapon* Weapon) //Bu kod, Weapon'un Collision Handle'lamasi yuzunden sadece serverde calisiyor
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(false); //Bu kisim da sadece serverde calisiyor, yani degeri degistirmeden once silah varsa kapiyor
	}
	OverlappingWeapon = Weapon;
	if (IsLocallyControlled()) //Yani bu if check niye gerekli bilemedim //Bunu acikliyor galiba ama anlamadim 46. ders sonu //galiba serverde gelmiyor diye
	{
		if (OverlappingWeapon) OverlappingWeapon->ShowPickupWidget(true);
	}
}

void AStrikeCharacter::SetOverlappingDoor(class ADoor* Door)
{
	if (OverlappingDoor) OverlappingDoor->ShowDoorWidget(false);
	OverlappingDoor = Door;
	if (IsLocallyControlled() && OverlappingDoor) OverlappingDoor->ShowDoorWidget(true);
}

void AStrikeCharacter::OnRep_OverlappingWeapon(AWeapon* LastWeapon) //RepNotify'lar asla serverde calismaz! //Rep notify ile giren girdi degerleri, replikasyon olmadan onceki degeri dondurur, biraz kafa karistirici
{
	if (OverlappingWeapon) OverlappingWeapon->ShowPickupWidget(true);
	if (LastWeapon) LastWeapon->ShowPickupWidget(false);
}

void AStrikeCharacter::OnRep_OverlappingDoor(ADoor* LastDoor)
{
	if (OverlappingDoor) OverlappingDoor->ShowDoorWidget(true);
	if (LastDoor) LastDoor->ShowDoorWidget(false);
}

bool AStrikeCharacter::IsWeaponEquipped() { return Combat && Combat->EquippedWeapon; }//Yari replication ile ilgili sayilir bu aslinda, tum Clientlerde AnimInstance guncellemeleri ile ilgili

bool AStrikeCharacter::IsAiming() { return Combat && Combat->bAiming; } //Yari replication ile ilgili sayilir bu aslinda, tum Clientlerde AnimInstance guncellemeleri ile ilgili

AWeapon* AStrikeCharacter::GetEquippedWeapon() //Anim instance icin aslinda
{
	if (Combat == nullptr) return nullptr;
	return Combat->EquippedWeapon;
}

void AStrikeCharacter::OnRep_ReplicatedMovement() //Bu hem unreal default hem replicated bilemedim
{
	Super::OnRep_ReplicatedMovement();
	SimProxiesTurn();
	TimeSinceLastMovementReplication = 0.f;
}

void AStrikeCharacter::SimProxiesTurn()
{
	if (Combat == nullptr || Combat->EquippedWeapon == nullptr) return;
	
	bRotateRootBone = false;
	float Speed = CalculateSpeed();
	if (Speed > 0.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
		return;
	}
	
	ProxyRotationLastFrame = ProxyRotation;
	ProxyRotation = GetActorRotation();
	ProxyYaw = UKismetMathLibrary::NormalizedDeltaRotator(ProxyRotation, ProxyRotationLastFrame).Yaw;

	if (FMath::Abs(ProxyYaw) > TurnThreshold)
	{
		if (ProxyYaw > TurnThreshold) TurningInPlace = ETurningInPlace::ETIP_Right;
		else if (ProxyYaw < -TurnThreshold) TurningInPlace = ETurningInPlace::ETIP_Left;
		else TurningInPlace = ETurningInPlace::ETIP_NotTurning; //Bunu yukardaki ifin elsesi yapmamiz gerekmiyor mu ak
		return; //bunun yerine alttaki satiri else icine alamaz miydik:???
	}
	TurningInPlace = ETurningInPlace::ETIP_NotTurning;
}
#pragma endregion NetworkEvents

FVector AStrikeCharacter::GetHitTarget() const //Bunu bi da yoklayim network mu degil mi
{
	if (Combat == nullptr) return FVector();
	return Combat->HitTarget;
}

#pragma region Elimination //Btw Bunlar da network Event ama cok doldu orasi
void AStrikeCharacter::Elim()
{
	DropOrDestroyWeapons();
	Multicast_Elim();
	GetWorldTimerManager().SetTimer(
		ElimTimer,
		this,
		&AStrikeCharacter::ElimTimerFinished,
		ElimDelay);
}

void AStrikeCharacter::DropOrDestroyWeapons()
{
	if (Combat)
	{
		if (Combat->EquippedWeapon) DropOrDestroyWeapon(Combat->EquippedWeapon);
		if (Combat->SecondaryWeapon) DropOrDestroyWeapon(Combat->SecondaryWeapon);
	}
}

void AStrikeCharacter::DropOrDestroyWeapon(class AWeapon* Weapon)
{
	if (Weapon == nullptr) return;
	
	if (Weapon->bDestroyWeapon) Weapon->Destroy();
	else Weapon->Dropped();
}

void AStrikeCharacter::Multicast_Elim_Implementation()
{
	if (StrikePlayerController)
	{
		StrikePlayerController->SetHUDWeaponAmmo(0);
	}
	bElimmed = true;
	PlayElimMontage();
	if (DissolveMaterialInstance) //Start Dissolve Effect
	{
		DynamicDissolveMaterialInstance = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		for (int i = 0; i < GetMesh()->GetNumMaterials(); i ++) GetMesh()->SetMaterial(i, DynamicDissolveMaterialInstance); //adamda for dongusu yok Optimized karaktere gectigi icin, ama ben costimazsyon icin feda ettim onu
		DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Dissolve"), .55f);
		DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Glow"), 200.f);
	}
	StartDissolve(); //Bunu if icine atsam mi acaba
	//Disable Character Movement
	bDisableGameplay = true;
	GetCharacterMovement()->DisableMovement(); //Bu da bDisableGameplayden sonra eklendi bir caresine bakayim
	//
	if (Combat) Combat->FireButtonPressed(false); //cok da onemli degil bence
	//Disable collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Spawn ElimBot
	if (ElimBotEffect)
	{
		FVector ElimBotSpawnPoint(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 200.f);
		ElimBotComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ElimBotEffect, ElimBotSpawnPoint, GetActorRotation());
	}
	if (ElimBotSound) UGameplayStatics::PlaySoundAtLocation(this, ElimBotSound, GetActorLocation());
	if (IsLocallyControlled() && Combat && Combat->bAiming && Combat->EquippedWeapon && Combat->EquippedWeapon->GetWeaponType() == EWeaponType::EWT_SniperRifle) ShowSniperScopeWidget(false); //local boola bagladi da gerek yok btw
}

void AStrikeCharacter::StartDissolve()
{
	DissolveTrack.BindDynamic(this, &AStrikeCharacter::UpdateDissolveMaterial);
	if (DissolveCurve && DissolveTimeline)
	{
		DissolveTimeline->AddInterpFloat(DissolveCurve, DissolveTrack);
		DissolveTimeline->Play(); //Play from start yapilabilir belki
	}
}

void AStrikeCharacter::UpdateDissolveMaterial(float DissolveValue)
{
	if (DynamicDissolveMaterialInstance) DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Dissolve"), DissolveValue);
}

void AStrikeCharacter::ElimTimerFinished() //Timer sadece serverde acildigindan, gamemode a erismek safe
{
	AStrikeGameMode* StrikeGameMode = GetWorld()->GetAuthGameMode<AStrikeGameMode>();
	if (StrikeGameMode)
	{
		StrikeGameMode->RequestRespawn(this, Controller/*GameMode'da controlleri check ediyoruz zaten, this girdisinin de null olacak hali yok herhal*/);
	}
}
#pragma endregion Elimination

void AStrikeCharacter::PollInit()
{
	if (StrikePlayerState == nullptr)
	{
		StrikePlayerState = GetPlayerState<AStrikePlayerState>(); //iste bu first frame de null donduruyor
		if (StrikePlayerState)
		{
			StrikePlayerState->AddToScore(0.f); //0 yaziriyoruz eklenmiyo moruk
			StrikePlayerState->AddToKills(0);
			StrikePlayerState->AddToDeaths(0);
		}
	}
}

ECombatState AStrikeCharacter::GetCombatState() const
{
	if (Combat == nullptr) return ECombatState::ECS_MAX;
	return Combat->CombatState;
}

void AStrikeCharacter::SpawnDefaultWeapon()
{
	AStrikeGameMode* StrikeGameMode = Cast<AStrikeGameMode>(UGameplayStatics::GetGameMode(this));
	UWorld* World = GetWorld();
	if (StrikeGameMode && World && !bElimmed && DefaultWeaponClass) //bunun null olmamasinin iki yolu var, birincisi zaten server olmamiz gerekiyor, ikincisi lobbyde olursak silah cagirmiyor //bElimmede ihtiyac var mi bilmiyom
	{
		AWeapon* StartingWeapon = World->SpawnActor<AWeapon>(DefaultWeaponClass);
		StartingWeapon->bDestroyWeapon = true; //bu mantik kafama yatmadi da neyse, adam yere atinca kalacak gene, destroy fonksiyonunu silah sinifinin drop fonksiyonuna tasimak daha mantikli sanki
		if (Combat)
		{
			Combat->EquipWeapon(StartingWeapon);
		}
	}
}