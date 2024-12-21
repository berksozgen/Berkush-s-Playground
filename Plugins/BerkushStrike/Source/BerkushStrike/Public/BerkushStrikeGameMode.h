// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BerkushStrikeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSTRIKE_API ABerkushStrikeGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ABerkushStrikeGameMode();

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	void EndRound();
	
};
