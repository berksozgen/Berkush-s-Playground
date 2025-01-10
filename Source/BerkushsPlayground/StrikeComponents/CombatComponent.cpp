// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "CombatComponent.h"

#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "BerkushsPlayground/Weapon/Weapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "BerkushsPlayground/PlayerController/StrikePlayerController.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
//Debug Helpers
#include "DrawDebugHelpers.h"
#include "BerkushsPlayground/Weapon/Projectile.h"
#include "Sound/SoundCue.h"

#pragma region UnrealDefaults
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	BaseWalkSpeed = 600.f;
	AimWalkSpeed = 350.f;
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatComponent, EquippedWeapon);
	DOREPLIFETIME(UCombatComponent, SecondaryWeapon);
	DOREPLIFETIME(UCombatComponent, bAiming);
	DOREPLIFETIME_CONDITION(UCombatComponent, CarriedAmmo, COND_OwnerOnly); //Diger clientler icin onemli degil bu
	DOREPLIFETIME(UCombatComponent, CombatState);
	DOREPLIFETIME(UCombatComponent, GrenadeCount); //buna niye condition koymadik
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Character)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

		if (Character->GetFollowCamera())
		{
			DefaultFOV = Character->GetFollowCamera()->FieldOfView;
			CurrentFOV = DefaultFOV;
		}
		if (Character->HasAuthority())
		{
			InitializeCarriedAmmo();
		}
	}
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (Character && Character->IsLocallyControlled())
	{
		FHitResult HitResult;
		TraceUnderCrosshairs(HitResult);
		HitTarget=HitResult.ImpactPoint;
		
		SetHUDCrosshairs(DeltaTime); //Bunlardaki Character == null Checkini kaldirmaliyim bi ara
		InterpFOV(DeltaTime); //Aha bundan da
	}
}
#pragma endregion UnrealDefaults

#pragma region OwnerOnly
void UCombatComponent::SetHUDCrosshairs(float DeltaTime)
{
	if (Character == nullptr || Character->Controller == nullptr) return;

	Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		HUD = HUD == nullptr ? Cast<AStrikeHUD>(Controller->GetHUD()) : HUD;
		if (HUD)
		{
			if (EquippedWeapon)
			{
				HUDPackage.CrosshairCenter = EquippedWeapon->CrosshairsCenter;
				HUDPackage.CrosshairsLeft = EquippedWeapon->CrosshairsLeft;
				HUDPackage.CrosshairsRight = EquippedWeapon->CrosshairsRight;
				HUDPackage.CrosshairsTop = EquippedWeapon->CrosshairsTop;
				HUDPackage.CrosshairsBottom = EquippedWeapon->CrosshairsBottom;
			}
			else
			{
				HUDPackage.CrosshairCenter = nullptr;
				HUDPackage.CrosshairsLeft = nullptr;
				HUDPackage.CrosshairsRight = nullptr;
				HUDPackage.CrosshairsTop = nullptr;
				HUDPackage.CrosshairsBottom = nullptr;
			}
			//Calculate Crosshair Spread

			//Map our Speed(between 0-600 i quess) to 0-1 because we scale it in hud
			FVector2D WalkSpeedRange(0.f, Character->GetCharacterMovement()->MaxWalkSpeed);
			FVector2D VelocityMultiplierRange(0.f,1.f);
			FVector Velocity = Character->GetVelocity();
			Velocity.Z = 0;
			CrosshairVelocityFactor = FMath::GetMappedRangeValueClamped(WalkSpeedRange,VelocityMultiplierRange, Velocity.Size()); //Burayi degistircem, Character->GetVelocity().Size() / Character->GetCharacterMovement()->MaxWalkSpeed ile

			if (Character->GetCharacterMovement()->IsFalling()) //Burda da Z yi sifirlamazsam bunu heaba katmis oluyorum zaten, ciddili single line a indirebilirim bunu
			{
				CrosshairInAirFactor = FMath::FInterpTo(CrosshairInAirFactor, 2.25f, DeltaTime, 2.25f);
			}
			else CrosshairInAirFactor = FMath::FInterpTo(CrosshairInAirFactor, 0.f, DeltaTime, 30.f);

			CrosshairAimFactor = FMath::FInterpTo(CrosshairAimFactor, bAiming ? -.58f : 0.f, DeltaTime, 30.f);

			CrosshairShootingFactor = FMath::FInterpTo(CrosshairShootingFactor, 0.f, DeltaTime, 40.f);
			
			HUDPackage.CrosshairSpread =
				.5f +
				CrosshairVelocityFactor +
					CrosshairInAirFactor +
						CrosshairAimFactor +
							CrosshairShootingFactor; 
			
			HUD->SetHUDPackage(HUDPackage);
		}
	}
}

void UCombatComponent::InterpFOV(float DeltaTime)
{
	if (EquippedWeapon == nullptr) return;

	if (bAiming) CurrentFOV = FMath::FInterpTo(CurrentFOV, EquippedWeapon->GetZoomedFOV(), DeltaTime, EquippedWeapon->GetZoomInterpSpeed());
	else CurrentFOV = FMath::FInterpTo(CurrentFOV, DefaultFOV, DeltaTime, ZoomInterpSpeed);
	
	if (Character && Character->GetFollowCamera()) Character->GetFollowCamera()->SetFieldOfView(CurrentFOV);
}

void UCombatComponent::TraceUnderCrosshairs(FHitResult& TraceHitResult)
{
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport) GEngine->GameViewport->GetViewportSize(ViewportSize);
	
	FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f); //They are in ScreenSpace, We need to Convert them WorldSpace
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection; //1 Birim uzerinden veriyor
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this/*Bu World'de olan bir obje istiyor, this demek mantikli GetWorld demek yerine*/, 0/*Oyun Multiplayer olsa bile PlayerControllerIndex 0 her zaman oyunu oynayan kisi oluyor*/),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection);
	
	if (bScreenToWorld)
	{
		FVector Start = CrosshairWorldPosition;
		if (Character) //Buna da gerek var mi bilmiyorum, ifte control ediliyor sonucta
		{
			float DistanceToCharacter = (Character->GetActorLocation() - Start).Size();
			Start += CrosshairWorldDirection * (DistanceToCharacter + 100.f);
		}
		FVector End = Start + CrosshairWorldDirection * TRACE_LENGHT;

		GetWorld()->LineTraceSingleByChannel(
			TraceHitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility);

		if (TraceHitResult.GetActor() && TraceHitResult.GetActor()->Implements<UInteractWithCrosshairsInterface>())
		{
			HUDPackage.CrosshairsColor = FLinearColor::Red;
		}
		else
		{
			HUDPackage.CrosshairsColor = FLinearColor::White;
		}
		if (!TraceHitResult.bBlockingHit) TraceHitResult.ImpactPoint = End; //Adam havaya sikarsa diye
	}
}

void UCombatComponent::UpdateWeaponAmmoTypeText(EWeaponType WeaponType)
{
	if (Controller == nullptr) return;
	FString WeaponTypeString(TEXT(""));
	switch(WeaponType)
	{
	case EWeaponType::EWT_AssaultRifle:
		WeaponTypeString = FString(TEXT("Assault Rifle"));
		break;
	case EWeaponType::EWT_Pistol:
		WeaponTypeString = FString(TEXT("Pistol"));
		break;
	case EWeaponType::EWT_SniperRifle:
		WeaponTypeString = FString(TEXT("Sniper Rifle"));
		break;
	case EWeaponType::EWT_RocketLauncher:
		WeaponTypeString = FString(TEXT("Rocket Launcher"));
		break;
	case EWeaponType::EWT_SubMachineGun:
		WeaponTypeString = FString(TEXT("SubMachine Gun"));
		break;
	case EWeaponType::EWT_Shotgun:
		WeaponTypeString = FString(TEXT("Shotgun"));
		break;
	case EWeaponType::EWT_GrenadeLauncher:
		WeaponTypeString = FString(TEXT("Grenade Launcher"));
		break;
	default:
		WeaponTypeString = FString(TEXT(""));
		break;
	}
	Controller->SetHUDWeaponAmmoType(WeaponTypeString);
}
#pragma endregion OwnerOnly

void UCombatComponent::SetAiming(bool bIsAiming)
{
	if (Character == nullptr || EquippedWeapon == nullptr) return;
	bAiming = bIsAiming; //Client serverden geri donus beklemeden animasyonu guncellesin diye
	Server_SetAiming(bIsAiming);
	if (Character) Character->GetCharacterMovement()->MaxWalkSpeed = bIsAiming ? AimWalkSpeed : BaseWalkSpeed;
	if (Character->IsLocallyControlled() && EquippedWeapon->GetWeaponType() == EWeaponType::EWT_SniperRifle)
	{
		Character->ShowSniperScopeWidget(bIsAiming);
	}
	
	/*
	if (!Character->HasAuthority())
	{
		Server_SetAiming(bIsAiming); //Bu wrape gerek var mi bilmiyorum, sonucta server kendinde de RPC cagirsa giren cikan olmayacak
	}//Adam benim dedigimi dedi ak sonradan, neyse comment atayim da sonra kafam karisirsa bakarim
	*/
}
void UCombatComponent::Server_SetAiming_Implementation(bool bIsAiming) //bAiming Replicated diye multicast atmaya gerek yok, Replicated degiskenler Server'dan tum Clientlere olacak sekilde esleniyor
{
	bAiming = bIsAiming;

	if (Character) Character->GetCharacterMovement()->MaxWalkSpeed = bIsAiming ? AimWalkSpeed : BaseWalkSpeed;
}

#pragma region Firing
void UCombatComponent::Fire()
{
	if (CanFire())
	{
		bCanFire = false;
		Server_Fire(HitTarget); /*BTW FHitResult zaten net optimized variable donduruyormus (20bit lokasyoan falan), Unreal :D*/
		if (EquippedWeapon) //Silahimiz yokken crosshairmiz yok ki bu adam bu checki niye yapti
		{
			CrosshairShootingFactor = .75f;
		}
		StartFireTimer();
	}
}

void UCombatComponent::FireButtonPressed(bool bPressed) { bFireButtonPressed = bPressed; if (bFireButtonPressed) Fire(); } //msvc agladi buna if ((bFireButtonPressed = bPressed)) Fire();

void UCombatComponent::StartFireTimer()
{
	if (EquippedWeapon == nullptr || Character == nullptr) return;
	Character->GetWorldTimerManager().SetTimer(
		FireTimer,
		this,
		&UCombatComponent::FireTimerFinished,
		EquippedWeapon->FireDelay);
}

void UCombatComponent::FireTimerFinished()
{
	bCanFire = true;
	if (EquippedWeapon == nullptr) return;
	if (bFireButtonPressed && EquippedWeapon->bAutomatic) Fire();
	ReloadEmptyWeapon();
}

void UCombatComponent::Server_Fire_Implementation(const FVector_NetQuantize& TraceHitTarget) { Multicast_Fire(TraceHitTarget); }
void UCombatComponent::Multicast_Fire_Implementation(const FVector_NetQuantize& TraceHitTarget)
{
	if (EquippedWeapon == nullptr) return;

	if (Character && CombatState == ECombatState::ECS_Reloading && EquippedWeapon->GetWeaponType() == EWeaponType::EWT_Shotgun)
	{
		Character->PlayFireMontage(bAiming);
		EquippedWeapon->Fire(TraceHitTarget);
		CombatState = ECombatState::ECS_Unoccupied;
		return; //else if te cakabilirdim gerci bu da shotgun eceptionu
	}
	if (Character && CombatState == ECombatState::ECS_Unoccupied)
	{
		Character->PlayFireMontage(bAiming);
		EquippedWeapon->Fire(TraceHitTarget);
	}
}

bool UCombatComponent::CanFire()
{
	if (EquippedWeapon == nullptr) return false;
	if (!EquippedWeapon->IsEmpty() && bCanFire && CombatState == ECombatState::ECS_Reloading && EquippedWeapon->GetWeaponType() == EWeaponType::EWT_Shotgun) return true; //shotgun icin exceptioon moruk
	return !EquippedWeapon->IsEmpty() && bCanFire && CombatState == ECombatState::ECS_Unoccupied;
}
#pragma endregion Firing

#pragma region Grenade
void UCombatComponent::ThrowGrenade()
{
	if (GrenadeCount == 0) return;
	if (CombatState != ECombatState::ECS_Unoccupied || EquippedWeapon == nullptr) return;
	
	CombatState = ECombatState::ECS_ThrowingGrenade;
	if (Character)
	{
		Character->PlayThrowGrenadeMontage();
		AttachActorToLeftHand(EquippedWeapon);
		ShowAttachedGrenade(true);
	}
	if (Character && !Character->HasAuthority())
	{
		Server_ThrowGrenade();
	}
	if (Character && Character->HasAuthority())
	{
		GrenadeCount == FMath::Clamp(GrenadeCount - 1, 0, MaxGrenadeCount);
		UpdateHUDGrenades();
	}
}

void UCombatComponent::Server_ThrowGrenade_Implementation()
{
	if (GrenadeCount == 0) return; //anti cheat moruk
	CombatState = ECombatState::ECS_ThrowingGrenade;
	if (Character)
	{
		Character->PlayThrowGrenadeMontage();
		AttachActorToLeftHand(EquippedWeapon);
		ShowAttachedGrenade(true);
	}
	GrenadeCount == FMath::Clamp(GrenadeCount - 1, 0, MaxGrenadeCount);
	UpdateHUDGrenades();
}

void UCombatComponent::UpdateHUDGrenades()
{
	Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		Controller->SetHUDGrenades(GrenadeCount);
	}
}

void UCombatComponent::ShowAttachedGrenade(bool bShowGrenade)
{
	if (Character && Character->GetAttachedGrenade()) Character->GetAttachedGrenade()->SetVisibility(bShowGrenade);
}

void UCombatComponent::ThrowGrenadeFinished()
{
	CombatState = ECombatState::ECS_Unoccupied;
	AttachActorToRightHand(EquippedWeapon);
}

void UCombatComponent::LaunchGrenade()
{
	ShowAttachedGrenade(false);
	if (Character && Character->IsLocallyControlled()) //bunu zaten ABP cagiriyor, characterin null olma ihtimali yok sanki
	{
		Server_LaunchGrenade(HitTarget);
	}
}

void UCombatComponent::Server_LaunchGrenade_Implementation(const FVector_NetQuantize& Target)
{
	if (Character && GrenadeClass && Character->GetAttachedGrenade())
	{
		const FVector StartingLocation = Character->GetAttachedGrenade()->GetComponentLocation();
		FVector ToTarget = Target - StartingLocation;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Character;
		SpawnParams.Instigator = Character;
		UWorld* World = GetWorld();
		if (World)
		{
			World->SpawnActor<AProjectile>(
				GrenadeClass,
				StartingLocation,
				ToTarget.Rotation(),
				SpawnParams);
		}
	}
}
#pragma endregion Grenade

#pragma region Reload
void UCombatComponent::Reload()
{
	if (CarriedAmmo > 0 && CombatState == ECombatState::ECS_Unoccupied && EquippedWeapon && !EquippedWeapon->IsFull())
	{
		Server_Reload();
	}
}

void UCombatComponent::ShotgunShellReload()
{
	if (Character && Character->HasAuthority())
	{
		UpdateShotgunAmmoValues();
	}
}

void UCombatComponent::Server_Reload_Implementation()
{
	if (Character == nullptr) return;//Mermiyi burda da checklesem iyi olabilir
	CombatState = ECombatState::ECS_Reloading;
	HandleReload();
}

void UCombatComponent::FinishReloading()
{
	if (Character == nullptr) return;
	if (Character->HasAuthority()) //yahu zaten bunu sadece server cagirmicak mi, serverda nullcheck de atiyoruz otorite check de //He anim notify ile cagircakmisiz bunu
	{
		CombatState = ECombatState::ECS_Unoccupied;
		UpdateAmmoValues();
	}
	if (bFireButtonPressed)
	{
		Fire();
	}
}

void UCombatComponent::UpdateAmmoValues()
{
	if (Character == nullptr || EquippedWeapon == nullptr) return;
	
	int32 ReloadAmount = AmountToReload();
	if (CarriedAmmoMap.Contains(EquippedWeapon->GetWeaponType()))
	{
		CarriedAmmoMap[EquippedWeapon->GetWeaponType()] -= ReloadAmount;
		CarriedAmmo = CarriedAmmoMap[EquippedWeapon->GetWeaponType()];
	}
	Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		Controller->SetHUDCarriedAmmo(CarriedAmmo);
	}
	EquippedWeapon->AddAmmo(-ReloadAmount);
}

void UCombatComponent::UpdateShotgunAmmoValues()
{
	if (Character == nullptr || EquippedWeapon == nullptr) return;
	
	if (CarriedAmmoMap.Contains(EquippedWeapon->GetWeaponType())) //aslinda hardcoded shotgun yapabilirim buraya da,revolver eklersem ayni mantigi kullancam
	{
		CarriedAmmoMap[EquippedWeapon->GetWeaponType()] -= 1;
		CarriedAmmo = CarriedAmmoMap[EquippedWeapon->GetWeaponType()];
	}
	Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		Controller->SetHUDCarriedAmmo(CarriedAmmo);
	}
	EquippedWeapon->AddAmmo(-1);
	bCanFire = true;
	if (EquippedWeapon->IsFull() || CarriedAmmo == 0)
	{
		JumpToShotgunEnd(); //bunu clientlerde gostermek icin weapon sinifinin on_rep ammosunda yapiyoruz aklima yatmadi pek
	}
}

void UCombatComponent::JumpToShotgunEnd()
{
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (AnimInstance && Character->GetReloadMontage())
	{
		AnimInstance->Montage_JumpToSection(FName("ShotgunEnd"));
	}
}

void UCombatComponent::HandleReload()
{
	Character->PlayReloadMontage();
}

int32 UCombatComponent::AmountToReload()
{
	if (EquippedWeapon == nullptr) return 0;
	int32 RoomInMag = EquippedWeapon->GetMagCapacity() - EquippedWeapon->GetAmmo();
	
	if (CarriedAmmoMap.Contains(EquippedWeapon->GetWeaponType()))
	{
		int32 AmountCarried = CarriedAmmoMap[EquippedWeapon->GetWeaponType()];
		int32 Least = FMath::Min(RoomInMag, AmountCarried);
		return FMath::Clamp(RoomInMag, 0, Least); //Biraz hata engelleme seyi, esseklik yapip weaponu spawnlarken 50 mermi icinde, magazine 30 mermi dersek RoomInMag - 20 olcak, taklaya gelcez
	}
	return 0;
}
#pragma endregion Reload

#pragma region RepNotifies
void UCombatComponent::OnRep_CombatState()
{
	switch (CombatState)
	{
	case ECombatState::ECS_Reloading:
		HandleReload();
		break;
	case ECombatState::ECS_Unoccupied:
		if (bFireButtonPressed)
		{
			Fire();
		}
		break;
	case ECombatState::ECS_ThrowingGrenade:
		if (Character && !Character->IsLocallyControlled())
		{
			Character->PlayThrowGrenadeMontage();
			AttachActorToLeftHand(EquippedWeapon);
			ShowAttachedGrenade(true);
		}
		break;
	}
}

void UCombatComponent::OnRep_EquippedWeapon()
{
	if (EquippedWeapon && Character)
	{
		EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);//Bunlari buraya da ekledi, ustteki fonksiyon time safe degil diye//He tamam yukardaki serverde calisiyor, bu clientte, silahimiz simdi fizik tabanli diye attach atamiyoruz//O yuzden serverden gelen yanittan once kendimiz fizikleri kaptioyuz, onu da set weapon state fonksiyonu hallediyor zaten
		AttachActorToRightHand(EquippedWeapon);
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
		Character->bUseControllerRotationYaw = true;
		//UpdateWeaponAmmoTypeText(EquippedWeapon->GetWeaponType()); //bunun icin dogru yer mi bilmiyorum
		PlayEquipWeaponSound(EquippedWeapon);
		EquippedWeapon->EnableCustomDepth(false); //buna gerek var mi bilmiyorum silebilirim bunu
		EquippedWeapon->SetHUDAmmo();
	}
}

void UCombatComponent::OnRep_SecondaryWeapon()
{
	if (SecondaryWeapon && Character)
	{
		SecondaryWeapon->SetWeaponState(EWeaponState::EWS_EquippedSecondary);
		AttachActorToBackpack(SecondaryWeapon);
		PlayEquipWeaponSound(SecondaryWeapon);
	}
}

void UCombatComponent::OnRep_CarriedAmmo()
{
	Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		Controller->SetHUDCarriedAmmo(CarriedAmmo);
	}
	bool bJumpToShotgunEnd = CombatState == ECombatState::ECS_Reloading &&
		EquippedWeapon != nullptr && EquippedWeapon->GetWeaponType() == EWeaponType::EWT_Shotgun &&
			CarriedAmmo == 0;
	if (bJumpToShotgunEnd) JumpToShotgunEnd();
}

void UCombatComponent::OnRep_GrenadeCount()
{
	UpdateHUDGrenades();
}
#pragma endregion RepNotifies

void UCombatComponent::InitializeCarriedAmmo()
{
	CarriedAmmoMap.Emplace(EWeaponType::EWT_AssaultRifle, StartingAssaultRifleAmmo);
	CarriedAmmoMap.Emplace(EWeaponType::EWT_RocketLauncher, StartingRocketAmmo);
	CarriedAmmoMap.Emplace(EWeaponType::EWT_Pistol, StartingPistolAmmo);
	CarriedAmmoMap.Emplace(EWeaponType::EWT_SubMachineGun, StartingSubMachineGunAmmo);
	CarriedAmmoMap.Emplace(EWeaponType::EWT_Shotgun, StartingShotgunAmmo);
	CarriedAmmoMap.Emplace(EWeaponType::EWT_SniperRifle, StartingSniperRifleAmmo);
	CarriedAmmoMap.Emplace(EWeaponType::EWT_GrenadeLauncher, StartingGrenadeLauncherAmmo);
}

void UCombatComponent::EquipWeapon(class AWeapon* WeaponToEquip)
{
	if (Character == nullptr || WeaponToEquip == nullptr) return;
	if (CombatState != ECombatState::ECS_Unoccupied) return;

	if (EquippedWeapon != nullptr && SecondaryWeapon == nullptr)
	{
		EquipSecondaryWeapon(WeaponToEquip);
	}
	else
	{
		EquipPrimaryWeapon(WeaponToEquip);
	}
	
	Character->GetCharacterMovement()->bOrientRotationToMovement = false;//1 Bunlari burada birakma nedenizim repnotifylar sadece clientlerde calisiyor, serverde calismiyor
	Character->bUseControllerRotationYaw = true;//1
}

void UCombatComponent::SwapWeapons()
{
	AWeapon* TempWeapon = EquippedWeapon;
	EquippedWeapon = SecondaryWeapon;
	SecondaryWeapon = TempWeapon;

	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	AttachActorToRightHand(EquippedWeapon);
	EquippedWeapon->SetHUDAmmo();
	UpdateCarriedAmmo();
	PlayEquipWeaponSound(EquippedWeapon);
	ReloadEmptyWeapon();

	SecondaryWeapon->SetWeaponState(EWeaponState::EWS_EquippedSecondary);
	AttachActorToBackpack(SecondaryWeapon);
}

bool UCombatComponent::ShouldSwapWeapons()
{
	return (EquippedWeapon != nullptr && SecondaryWeapon != nullptr);
}

void UCombatComponent::EquipPrimaryWeapon(AWeapon* WeaponToEquip)
{
	DropEquippedWeapon();
	EquippedWeapon = WeaponToEquip;
	if (EquippedWeapon == nullptr) return; //burda ve secondary de nullcheck gerekli mi bilemedim
	
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	AttachActorToRightHand(EquippedWeapon);
	EquippedWeapon->SetOwner(Character);
	EquippedWeapon->SetHUDAmmo(); //Weapon da bahsettigim kisim burasiydi
	UpdateCarriedAmmo();
	PlayEquipWeaponSound(EquippedWeapon);
	ReloadEmptyWeapon();
}

void UCombatComponent::EquipSecondaryWeapon(AWeapon* WeaponToEquip)
{
	SecondaryWeapon = WeaponToEquip;
	if (SecondaryWeapon == nullptr) return;
	
	SecondaryWeapon->SetWeaponState(EWeaponState::EWS_EquippedSecondary);
	AttachActorToBackpack(SecondaryWeapon);
	SecondaryWeapon->SetOwner(Character);
	PlayEquipWeaponSound(SecondaryWeapon);
}

void UCombatComponent::DropEquippedWeapon()
{
	if (EquippedWeapon) EquippedWeapon->Dropped();
}

void UCombatComponent::AttachActorToRightHand(AActor* ActorToAttach)
{
	if (Character == nullptr || Character->GetMesh() == nullptr || ActorToAttach == nullptr) return;
	const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocket"));
	if (HandSocket) HandSocket->AttachActor(ActorToAttach, Character->GetMesh());
}

void UCombatComponent::AttachActorToLeftHand(AActor* ActorToAttach)
{
	if (Character == nullptr || Character->GetMesh() == nullptr || ActorToAttach == nullptr) return;
	const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("LeftHandSocket"));
	if (HandSocket) HandSocket->AttachActor(ActorToAttach, Character->GetMesh());
}

void UCombatComponent::AttachActorToBackpack(AActor* ActorToAttach)
{
	if (Character == nullptr || Character->GetMesh() == nullptr || ActorToAttach == nullptr) return;
	const USkeletalMeshSocket* BackpackSocket = Character->GetMesh()->GetSocketByName(FName("BackpackSocket"));
	if (BackpackSocket) BackpackSocket->AttachActor(ActorToAttach, Character->GetMesh());
}

void UCombatComponent::UpdateCarriedAmmo()
{
	if (EquippedWeapon == nullptr) return;
	
	if (CarriedAmmoMap.Contains(EquippedWeapon->GetWeaponType()))
	{
		CarriedAmmo = CarriedAmmoMap[EquippedWeapon->GetWeaponType()];
	}
	
	Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		Controller->SetHUDCarriedAmmo(CarriedAmmo);
		UpdateWeaponAmmoTypeText(EquippedWeapon->GetWeaponType());
	}
}

void UCombatComponent::PlayEquipWeaponSound(AWeapon* WeaponToEquip)
{
	if (Character && WeaponToEquip && WeaponToEquip->EquipSound) UGameplayStatics::PlaySoundAtLocation(this, WeaponToEquip->EquipSound, Character->GetActorLocation());
}

void UCombatComponent::ReloadEmptyWeapon() { if (EquippedWeapon && EquippedWeapon->IsEmpty()) Reload(); }

void UCombatComponent::PickupAmmo(EWeaponType WeaponType, int32 AmmoAmount)
{
	if (CarriedAmmoMap.Contains(WeaponType))
	{
		CarriedAmmoMap[WeaponType] += AmmoAmount;
		UpdateCarriedAmmo();
	}
	if (EquippedWeapon && EquippedWeapon->IsEmpty() && EquippedWeapon->GetWeaponType() == WeaponType)
	{
		Reload();
	}
}