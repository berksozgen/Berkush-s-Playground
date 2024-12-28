// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BerkushStrikeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSTRIKE_API ABerkushStrikeGameMode : public AGameMode
{
	GENERATED_BODY()

	ABerkushStrikeGameMode();

	virtual void OnPostLogin(AController* NewPlayer) override;
	
	TSubclassOf<APawn> PlayerPawnClass;
	
};
