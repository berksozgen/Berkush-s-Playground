// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "BerkushStrikeGameState.h"

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
