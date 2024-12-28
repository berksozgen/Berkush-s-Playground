// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "BerkushStrikeGameState.h"
#include "BerkushStrikePlayerState.h"
#include "Net/UnrealNetwork.h"

ABerkushStrikeGameState::ABerkushStrikeGameState() :
	WinningPlayer(-1)
{
	
}

void ABerkushStrikeGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABerkushStrikeGameState, WinningPlayer);
}

void ABerkushStrikeGameState::OnRep_Winner()
{
	if (WinningPlayer >= 0) OnVictory();
}

void ABerkushStrikeGameState::TriggerRestart_Implementation()
{
	OnRestart();
}

ABerkushStrikePlayerState* ABerkushStrikeGameState::GetPlayerStateByIndex(int PlayerIndex)
{
	for (APlayerState* PS : PlayerArray)
	{
		ABerkushStrikePlayerState* State = Cast<ABerkushStrikePlayerState>(PS);
		if (State && State->PlayerIndex == PlayerIndex) return State;
	}

	return nullptr;
}


//Bunlar benim
void ABerkushStrikeGameState::StartRound()
{
	//Spawn Weapons
	
	//Respawn Players

	//Set Timer
	GetWorldTimerManager().SetTimer(
		RemainingTimeHandle,
		this,
		&ABerkushStrikeGameState::RemainingTimeFunction,
		1.0f,
		true
		);
}

void ABerkushStrikeGameState::EndRound()
{
	if(RedTeamAlivePlayers > 0 && BlueTeamAlivePlayers > 0); // Round cross
	else if(RedTeamAlivePlayers > 0) RedTeamScore++;
	else BlueTeamScore++;

	//Play Sound
	//Show EndRound Widget
	//Start Round
}

void ABerkushStrikeGameState::RemainingTimeFunction()
{
	RemainingTime--;
	if(RemainingTime<=0) EndRound();
}
