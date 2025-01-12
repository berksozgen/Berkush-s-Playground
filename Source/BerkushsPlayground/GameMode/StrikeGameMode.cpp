// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "StrikeGameMode.h"
#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "BerkushsPlayground/GameState/StrikeGameState.h"
#include "BerkushsPlayground/PlayerController/StrikePlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "BerkushsPlayground/PlayerState/StrikePlayerState.h"

namespace MatchState
{
	const FName Cooldown = FName("Cooldown"); // Unreal'in yaptigi gibi yaptik, aslinda externe falan hic gerek yok
}

AStrikeGameMode::AStrikeGameMode()
{
	bDelayedStart = true;
}

void AStrikeGameMode::BeginPlay()
{
	Super::BeginPlay();

	LevelStartingTime = GetWorld()->GetTimeSeconds(); //su mantik sacma geldi btw//anladim bunun mantigi oyun acildigindan beri unreal sure tutuyormus, editorde direkt game mapi acinca 0 oluyor tabi
}

void AStrikeGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MatchState == MatchState::WaitingToStart)
	{
		CountdownTime = WarmupTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			StartMatch();
		}
	}
	else if (MatchState == MatchState::InProgress)
	{
		CountdownTime = WarmupTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			SetMatchState(MatchState::Cooldown);
		}
	}
	else if (MatchState == MatchState::Cooldown)
	{
		CountdownTime = WarmupTime + MatchTime + CooldownTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			RestartGame(); //Reset level daha mi mantikli sanki //btw server travel sadece buildli oyunlarda calisiyormus ya da launch game dicen //btw seamlessi lobbyde cagirdik burada ihtiyacimiz var mi
		}
	}
}

void AStrikeGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) //Su iteratorlar ne ogrenmem lazim bi ara
	{
		AStrikePlayerController* StrikePlayer = Cast<AStrikePlayerController>(*It);
		if (StrikePlayer)
		{
			StrikePlayer->OnMatchStateSet(MatchState);	
		}
	}
}

void AStrikeGameMode::PlayerEliminated(AStrikeCharacter* ElimmedCharacter,
                                       AStrikePlayerController* VictimController, AStrikePlayerController* AttackerController)
{
	AStrikePlayerState* AttackerPlayerState = AttackerController ? Cast<AStrikePlayerState>(AttackerController->PlayerState/*niye get player state kullanmadik ki*/) : nullptr;
	AStrikePlayerState* VictimPlayerState = VictimController ? Cast<AStrikePlayerState>(VictimController->PlayerState) : nullptr;

	AStrikeGameState* StrikeGameState = GetGameState<AStrikeGameState>();

	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState && StrikeGameState)
	{
		AttackerPlayerState->AddToScore(14.07f);
		AttackerPlayerState->AddToKills(1);
		StrikeGameState->UpdateTopScore(AttackerPlayerState);
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddToDeaths(1);
		if (VictimPlayerState == AttackerPlayerState) VictimPlayerState->AddToScore(-14.07f);
		else VictimPlayerState->AddToScore(-7.14f);
	}
	
	if (ElimmedCharacter) ElimmedCharacter->Elim();
}

void AStrikeGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Reset(); //Destroy atmadan bunu cagirma nedenimiz Datalari kaybolmasin diye
		ElimmedCharacter->Destroy();
	}
	if (ElimmedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts); //He bunlar statik fonksiyon oldugu icin world'u weya world context objelerini istiyormus, aydinlandim ak
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(ElimmedController, PlayerStarts[Selection]); /*BTW respawn atarken oldugu yere en yakin olani/diger oyunculardan en uzak olani veya takimsal mantikla yapabilirim, gene aydinlandim*/
	}
}