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

void AStrikePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetHUDTime();
	CheckTimeSync(DeltaTime);
}

void AStrikePlayerController::CheckTimeSync(float DeltaTime) //bunu timer handle a alabilirim belki
{
	TimeSyncRunningTime += DeltaTime;
	if (IsLocalController() && TimeSyncRunningTime > TimeSyncFrequency)
	{
		Server_RequestServerTime(GetWorld()->GetTimeSeconds());
		TimeSyncRunningTime = 0.f;
	}
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

void AStrikePlayerController::SetHUDMatchCountdown(float CountdownTime)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->MatchCountdownText; //siralama onemli btw
	
	if (bHUDValid)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - Minutes * 60;
		FString CountDownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds); //%02d 1 girdisini 01 yapiyor misal
		StrikeHUD->CharacterOverlay->MatchCountdownText->SetText(FText::FromString(CountDownText));
	}
}

void AStrikePlayerController::SetHUDTime()
{
	uint32 SecondsLeft = FMath::CeilToInt(MatchTime - GetServerTime());
	if (CountdownInt != SecondsLeft)
	{
		SetHUDMatchCountdown(MatchTime - GetServerTime()); // niye seconds left yapistirmadik ki direkt
	}
	CountdownInt = SecondsLeft;
}

void AStrikePlayerController::Server_RequestServerTime_Implementation(float TimeOfClientRequest)
{
	float ServerTimeOfReceipt = GetWorld()->GetTimeSeconds();
	Client_ReportServerTime(TimeOfClientRequest, ServerTimeOfReceipt);
}

void AStrikePlayerController::Client_ReportServerTime_Implementation(float TimeOfClientRequest,
	float TimeServerReceivedClientRequest)
{
	float RoundTripTime = GetWorld()->GetTimeSeconds() - TimeOfClientRequest;
	float CurrentServerTime = TimeServerReceivedClientRequest + (0.5f * RoundTripTime);
	ClientServerDelta = CurrentServerTime - GetWorld()->GetTimeSeconds();
}

float AStrikePlayerController::GetServerTime()
{
	return GetWorld()->GetTimeSeconds() + (HasAuthority()) ? 0.f : ClientServerDelta; //Adam has authority kaldirmis
}

void AStrikePlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	if (IsLocalController())
	{
		Server_RequestServerTime(GetWorld()->GetTimeSeconds());
	}
}
