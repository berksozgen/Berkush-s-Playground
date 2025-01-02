// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "StrikeGameMode.h"
#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "BerkushsPlayground/PlayerController/StrikePlayerController.h"

void AStrikeGameMode::PlayerEliminated(AStrikeCharacter* ElimmedCharacter,
	AStrikePlayerController* VictimController, AStrikePlayerController* AttackerController)
{
	if (ElimmedCharacter) ElimmedCharacter->Elim();
}
