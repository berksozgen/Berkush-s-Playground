// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "StrikePlayerState.h"
#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "BerkushsPlayground/PlayerController/StrikePlayerController.h"
#include "Net/UnrealNetwork.h"

void AStrikePlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AStrikePlayerState, Kills);
	DOREPLIFETIME(AStrikePlayerState, Deaths);
}

void AStrikePlayerState::AddToScore(float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount); //Duz member variable olan score deprached olmus
	
	Character = Character == nullptr ? Cast<AStrikeCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->GetController()) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());
		}
	}
}

void AStrikePlayerState::AddToKills(int32 KillsAmount)
{
	Kills += KillsAmount;
	
	Character = Character == nullptr ? Cast<AStrikeCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->GetController()) : Controller;
		if (Controller)
		{
			Controller->SetHUDKills(Kills);
		}
	}
}

void AStrikePlayerState::AddToDeaths(int32 DeathsAmount)
{
	Deaths += DeathsAmount;
	
	Character = Character == nullptr ? Cast<AStrikeCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->GetController()) : Controller;
		if (Controller)
		{
			Controller->SetHUDDeaths(Deaths);
		}
	}
}

void AStrikePlayerState::OnRep_Score() //That won't be never called on server
{
	Super::OnRep_Score(); //Rider bunu doldurmadi gerek yok bence

	Character = Character == nullptr ? Cast<AStrikeCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->GetController()) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());
		}
	}
}

void AStrikePlayerState::OnRep_Kills()
{
	Character = Character == nullptr ? Cast<AStrikeCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->GetController()) : Controller;
		if (Controller)
		{
			Controller->SetHUDKills(Kills);
		}
	}
}

void AStrikePlayerState::OnRep_Deaths()
{
	Character = Character == nullptr ? Cast<AStrikeCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AStrikePlayerController>(Character->GetController()) : Controller;
		if (Controller)
		{
			Controller->SetHUDDeaths(Deaths);
		}
	}
}