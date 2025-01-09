// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "StrikePlayerController.h"
#include "BerkushsPlayground/HUD/StrikeHUD.h"
#include "BerkushsPlayground/HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "Net/UnrealNetwork.h"
#include "BerkushsPlayground/GameMode/StrikeGameMode.h"
#include "BerkushsPlayground/GameState/StrikeGameState.h"
#include "BerkushsPlayground/HUD/Announcement.h"
#include "BerkushsPlayground/PlayerState/StrikePlayerState.h"
#include "BerkushsPlayground/StrikeComponents/CombatComponent.h"
#include "Kismet/GameplayStatics.h"

void AStrikePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	StrikeHUD = Cast<AStrikeHUD>(GetHUD());
	Server_CheckMatchState();
}

void AStrikePlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AStrikePlayerController, MatchState);
}

void AStrikePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetHUDTime();
	CheckTimeSync(DeltaTime);
	PollInit();
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

void AStrikePlayerController::Server_CheckMatchState_Implementation()
{
	AStrikeGameMode* GameMode = Cast<AStrikeGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		LevelStartingTime = GameMode->LevelStartingTime;
		WarmupTime = GameMode->WarmupTime;
		MatchTime = GameMode->MatchTime;
		MatchState = GameMode->GetMatchState();
		CooldownTime = GameMode->CooldownTime;
		Client_JoinMidGame(MatchState, LevelStartingTime, WarmupTime, MatchTime, CooldownTime);
	}
}

void AStrikePlayerController::Client_JoinMidGame_Implementation(FName _StateOfMatch, float _StartingTime, float _WarmupTime, float _MatchTime, float _CooldownTime) //replicated yerine boyle yaptik
{
	LevelStartingTime = _StartingTime;
	WarmupTime = _WarmupTime;
	MatchTime = _MatchTime;
	CooldownTime = _CooldownTime;
	MatchState = _StateOfMatch;
	OnMatchStateSet(MatchState);
	if (StrikeHUD && MatchState == MatchState::WaitingToStart)
	{
		StrikeHUD->AddAnnouncement();
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
	else
	{
		bInitializeCharacterOverlay = true;
		HUDHealth = Health;
		HUDMaxHealth = MaxHealth;
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
	else
	{
		bInitializeCharacterOverlay = true;
		HUDScore = Score;
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
	else
	{
		bInitializeCharacterOverlay = true;
		HUDKills = Kills;
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
	else
	{
		bInitializeCharacterOverlay = true;
		HUDDeaths = Deaths;
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
		if (CountdownTime < 0.0f)
		{
			StrikeHUD->CharacterOverlay->MatchCountdownText->SetText(FText());
			return;
		}
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - Minutes * 60;
		FString CountDownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds); //%02d 1 girdisini 01 yapiyor misal
		StrikeHUD->CharacterOverlay->MatchCountdownText->SetText(FText::FromString(CountDownText));
	}
}

void AStrikePlayerController::SetHUDAnnouncementCountdown(float CountdownTime)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->Announcement && StrikeHUD->Announcement->WarmupTime; //siralama onemli btw
	
	if (bHUDValid)
	{
		if (CountdownTime < 0.f)
		{
			StrikeHUD->Announcement->WarmupTime->SetText(FText());
			return;
		}
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - Minutes * 60;
		FString CountDownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds); //%02d 1 girdisini 01 yapiyor misal
		StrikeHUD->Announcement->WarmupTime->SetText(FText::FromString(CountDownText));
	}
}

void AStrikePlayerController::SetHUDGrenades(int32 Grenades)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->GrenadesText; //siralama onemli btw
	
	if (bHUDValid)
	{
		FString GrenadesText = FString::Printf(TEXT("%d"), Grenades);
		StrikeHUD->CharacterOverlay->GrenadesText->SetText(FText::FromString(GrenadesText));
	}
	else
	{
		HUDGrenades = Grenades;
	}
}

void AStrikePlayerController::SetHUDTime()
{
	float TimeLeft = 0.f;
	if (MatchState == MatchState::WaitingToStart) TimeLeft = WarmupTime - GetServerTime() + LevelStartingTime;
	else if (MatchState == MatchState::InProgress) TimeLeft = WarmupTime /*Burasi biraz degisik*/+ MatchTime - GetServerTime() + LevelStartingTime;
	else if (MatchState == MatchState::Cooldown) TimeLeft = WarmupTime + MatchTime + CooldownTime - GetServerTime() + LevelStartingTime;

	uint32 SecondsLeft = FMath::CeilToInt(TimeLeft);

	if (HasAuthority()) //Bu bloga ne gerek var bilemedim
	{
		StrikeGameMode = StrikeGameMode == nullptr ? Cast<AStrikeGameMode>(UGameplayStatics::GetGameMode(this)) : StrikeGameMode;
		if (StrikeGameMode)
		{
			SecondsLeft = FMath::CeilToInt(StrikeGameMode->GetCountdownTime() + LevelStartingTime); 
		}
	}
	
	if (CountdownInt != SecondsLeft)
	{
		if (MatchState == MatchState::WaitingToStart || MatchState == MatchState::Cooldown)
		{
			SetHUDAnnouncementCountdown(TimeLeft);
		}
		else if (MatchState == MatchState::InProgress)
		{
			SetHUDMatchCountdown(TimeLeft);
		}
	}
	CountdownInt = SecondsLeft;
}

void AStrikePlayerController::PollInit()
{
	if (CharacterOverlay == nullptr)
	{
		if (StrikeHUD && StrikeHUD->CharacterOverlay)
		{
			CharacterOverlay = StrikeHUD->CharacterOverlay;
			if (CharacterOverlay)
			{
				SetHUDHealth(HUDHealth,HUDMaxHealth);
				SetHUDScore(HUDScore);
				SetHUDKills(HUDKills);
				SetHUDDeaths(HUDDeaths);
				
				AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(GetPawn());
				if (StrikeCharacter && StrikeCharacter->GetCombat()) SetHUDGrenades(StrikeCharacter->GetCombat()->GetGrenadesCount());
			}
		}
	}
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
	return GetWorld()->GetTimeSeconds() + (HasAuthority() ? 0.f : ClientServerDelta); //Adam has authority kaldirmis
}

void AStrikePlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	if (IsLocalController())
	{
		Server_RequestServerTime(GetWorld()->GetTimeSeconds());
	}
}

void AStrikePlayerController::OnMatchStateSet(FName State) //just server because we call this function called from gamemode
{
	MatchState = State;
	
	if (MatchState == MatchState::InProgress) HandleMatchHasStarted();
	else if (MatchState == MatchState::Cooldown) HandleCooldown();
}

void AStrikePlayerController::OnRep_MatchState()
{
	if (MatchState == MatchState::InProgress) HandleMatchHasStarted();
	else if (MatchState == MatchState::Cooldown) HandleCooldown();
}

void AStrikePlayerController::HandleMatchHasStarted()
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;
	if (StrikeHUD)
	{
		if (StrikeHUD->CharacterOverlay == nullptr) StrikeHUD->AddCharacterOverlay();
		if (StrikeHUD->Announcement)
		{
			StrikeHUD->Announcement->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AStrikePlayerController::HandleCooldown()
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;
	if (StrikeHUD)
	{
		StrikeHUD->CharacterOverlay->RemoveFromParent();
		bool bHUDValid = StrikeHUD->Announcement && StrikeHUD->Announcement->AnnouncementText && StrikeHUD->Announcement->InfoText;
		
		if (bHUDValid)
		{
			StrikeHUD->Announcement->SetVisibility(ESlateVisibility::Visible);
			FString AnnouncementText("New Match Starts In:");
			StrikeHUD->Announcement->AnnouncementText->SetText(FText::FromString(AnnouncementText));

			AStrikeGameState* StrikeGameState = Cast<AStrikeGameState>(UGameplayStatics::GetGameState(this));
			AStrikePlayerState* StrikePlayerState = GetPlayerState<AStrikePlayerState>();
			FString InfoTextString(TEXT(""));
			if (StrikeGameState && StrikePlayerState)
			{
				TArray<AStrikePlayerState*> TopPlayers = StrikeGameState->TopScoringPlayers;
				if (TopPlayers.Num() == 0)
				{
					InfoTextString = FString("There is no winner!");
				}
				else if (TopPlayers.Num() == 1)
				{
					if (TopPlayers[0] == StrikePlayerState)
					{
						InfoTextString = FString("You are the Winner!");
					}
					else
					{
						InfoTextString = FString::Printf(TEXT("Winner: \n%s!"), *TopPlayers[0]->GetPlayerName());
					}
				}
				else if (TopPlayers.Num() > 1) //niye direkt else demedik ki
				{
					InfoTextString = FString("Players tied for the win: \n");
					for (auto TiedPlayer : TopPlayers)
					{
						InfoTextString.Append(FString::Printf(TEXT("%s \n"), *TiedPlayer->GetPlayerName()));
					}
				}
			}
			StrikeHUD->Announcement->InfoText->SetText(FText::FromString(InfoTextString));
		}
	}
	AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(GetPawn());
	if (StrikeCharacter && StrikeCharacter->GetCombat())
	{
		StrikeCharacter->bDisableGameplay = true; //Bunu yoketmek istiyorum ya aklima yatmadi
		StrikeCharacter->GetCombat()->FireButtonPressed(false); //bunu da eklemek icin bir suru sey yaptik ak
	}
}