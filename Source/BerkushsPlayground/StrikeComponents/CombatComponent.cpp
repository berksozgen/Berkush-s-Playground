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
	DOREPLIFETIME(UCombatComponent, bAiming);
	DOREPLIFETIME_CONDITION(UCombatComponent, CarriedAmmo, COND_OwnerOnly); //Diger clientler icin onemli degil bu
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
#pragma endregion OwnerOnly

void UCombatComponent::SetAiming(bool bIsAiming)
{
	bAiming = bIsAiming; //Client serverden geri donus beklemeden animasyonu guncellesin diye
	Server_SetAiming(bIsAiming);
	if (Character) Character->GetCharacterMovement()->MaxWalkSpeed = bIsAiming ? AimWalkSpeed : BaseWalkSpeed;
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

void UCombatComponent::FireButtonPressed(bool bPressed) { if ((bFireButtonPressed = bPressed)) Fire(); }

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
}

void UCombatComponent::Server_Fire_Implementation(const FVector_NetQuantize& TraceHitTarget) { Multicast_Fire(TraceHitTarget); }
void UCombatComponent::Multicast_Fire_Implementation(const FVector_NetQuantize& TraceHitTarget)
{
	if (EquippedWeapon == nullptr) return;
	
	if (Character)
	{
		Character->PlayFireMontage(bAiming);
		EquippedWeapon->Fire(TraceHitTarget);
	}
}
#pragma endregion Firing

void UCombatComponent::EquipWeapon(class AWeapon* WeaponToEquip)
{
	if (Character == nullptr || WeaponToEquip == nullptr) return;
	if (EquippedWeapon) //Elemanlar 50 tane silah almasin diye
	{
		EquippedWeapon->Dropped();
	}

	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
	const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocket"));
	if (HandSocket) HandSocket->AttachActor(EquippedWeapon, Character->GetMesh());
	EquippedWeapon->SetOwner(Character);
	EquippedWeapon->SetHUDAmmo(); //Weapon da bahsettigim kisim burasiydi

	if (CarriedAmmoMap.Contains(EquippedWeapon->GetWeaponType()))
	{
		CarriedAmmo = CarriedAmmoMap[EquippedWeapon->GetWeaponType()];
	}
	
	Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		Controller->SetHUDCarriedAmmo(CarriedAmmo);
	}
	
	Character->GetCharacterMovement()->bOrientRotationToMovement = false;//1 Bunlari burada birakma nedenizim repnotifylar sadece clientlerde calisiyor, serverde calismiyor
	Character->bUseControllerRotationYaw = true;//1
}

void UCombatComponent::Reload()
{
	if (CarriedAmmo > 0)
	{
		Server_Reload();
	}
}

void UCombatComponent::Server_Reload_Implementation()
{
	if (Character == nullptr) //Mermiyi burda da checklesem iyi olabilir
	{
		Character->PlayReloadMontage();
	}
}

void UCombatComponent::OnRep_EquippedWeapon()
{
	if (EquippedWeapon && Character)
	{
		EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);//Bunlari buraya da ekledi, ustteki fonksiyon time safe degil diye
		const USkeletalMeshSocket* HandSocket = Character->GetMesh()->GetSocketByName(FName("RightHandSocket"));//He tamam yukardaki serverde calisiyor, bu clientte, silahimiz simdi fizik tabanli diye attach atamiyoruz
		if (HandSocket) HandSocket->AttachActor(EquippedWeapon, Character->GetMesh());//O yuzden serverden gelen yanittan once kendimiz fizikleri kaptioyuz, onu da set weapon state fonksiyonu hallediyor zaten
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
		Character->bUseControllerRotationYaw = true;
	}
}

bool UCombatComponent::CanFire()
{
	if (EquippedWeapon == nullptr) return false;
	return !EquippedWeapon->IsEmpty() || !bCanFire;
}

void UCombatComponent::OnRep_CarriedAmmo()
{
	Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		Controller->SetHUDCarriedAmmo(CarriedAmmo);
	}
}

void UCombatComponent::InitializeCarriedAmmo()
{
	CarriedAmmoMap.Emplace(EWeaponType::EWT_AssaultRifle, StartingAssaultRifleAmmo);
}
