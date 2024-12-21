// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "BerkushStrikeGameMode.h"
#include "UObject/ConstructorHelpers.h"

ABerkushStrikeGameMode::ABerkushStrikeGameMode()
{
	//PrimaryActorTick.bCanEverTick = true;
	
}

AActor* ABerkushStrikeGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	return Super::ChoosePlayerStart_Implementation(Player);
}

void ABerkushStrikeGameMode::EndRound()
{
}