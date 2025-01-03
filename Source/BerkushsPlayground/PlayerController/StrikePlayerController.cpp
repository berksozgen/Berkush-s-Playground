// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "StrikePlayerController.h"
#include "BerkushsPlayground/HUD/StrikeHUD.h"
#include "BerkushsPlayground/HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "BerkushsPlayground/Character/StrikeCharacter.h"

void AStrikePlayerController::BeginPlay()
{
	Super::BeginPlay();

	 StrikeHUD = Cast<AStrikeHUD>(GetHUD());
}

void AStrikePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(InPawn);
	if (StrikeCharacter)
	{
		SetHUDHealth(StrikeCharacter->GetHealth(), StrikeCharacter->GetMaxHealth()); //Characteri'in beginplayeyinden bunu kaldirmama nedenimiz, ilk oyun basladiginda overlaylerin daha initiliza olmamasi
		SetHUDKilledText(FString(""));
		//SetKilledText(FText::FromString(TEXT("")));
	}
}

void AStrikePlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->HealthBar && StrikeHUD->CharacterOverlay->HealthText; //siralama onemli btw
	if (bHUDValid)
	{
		const float HealthPercent = Health / MaxHealth;
		StrikeHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		FString HealthText = FString::Printf(TEXT("%c%d"), '%', FMath::CeilToInt(100.f * HealthPercent));
		StrikeHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}

void AStrikePlayerController::SetHUDScore(float Score)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->ScoreAmount; //siralama onemli btw

	if (bHUDValid)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
		StrikeHUD->CharacterOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
	}
}

void AStrikePlayerController::SetHUDKills(int32 Kills)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->KillsAmount; //siralama onemli btw

	if (bHUDValid)
	{
		FString KillsText = FString::Printf(TEXT("%d"), Kills);
		StrikeHUD->CharacterOverlay->KillsAmount->SetText(FText::FromString(KillsText));
	}
}

void AStrikePlayerController::SetHUDDeaths(int32 Deaths)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->DeathsAmount; //siralama onemli btw
	
	if (bHUDValid)
	{
		FString DeathsText = FString::Printf(TEXT("%d"), Deaths);
		StrikeHUD->CharacterOverlay->DeathsAmount->SetText(FText::FromString(DeathsText));
	}
}

void AStrikePlayerController::SetHUDKilledText(FString KilledText)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->KilledText; //siralama onemli btw
	
	if (bHUDValid)
	{
		StrikeHUD->CharacterOverlay->KilledText->SetText(FText::FromString(KilledText));
	}
}

void AStrikePlayerController::SetHUDWeaponAmmo(int32 Ammo)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->WeaponAmmoAmount; //siralama onemli btw
	
	if (bHUDValid)
	{
		FString WeaponAmmoText = FString::Printf(TEXT("%d"), Ammo);
		StrikeHUD->CharacterOverlay->WeaponAmmoAmount->SetText(FText::FromString(WeaponAmmoText));
	}
}

void AStrikePlayerController::SetHUDCarriedAmmo(int32 Ammo)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->CarriedAmmoAmount; //siralama onemli btw
	
	if (bHUDValid)
	{
		FString CarriedAmmoText = FString::Printf(TEXT("%d"), Ammo);
		StrikeHUD->CharacterOverlay->CarriedAmmoAmount->SetText(FText::FromString(CarriedAmmoText));
	}
}

void AStrikePlayerController::SetHUDWeaponAmmoType(FString AmmoType)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->WeaponAmmoType; //siralama onemli btw
	
	if (bHUDValid)
	{
		StrikeHUD->CharacterOverlay->WeaponAmmoType->SetText(FText::FromString(AmmoType));
	}
}
