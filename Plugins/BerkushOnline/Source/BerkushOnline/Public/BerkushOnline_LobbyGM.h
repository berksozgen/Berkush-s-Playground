// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BerkushOnline_LobbyGM.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHONLINE_API ABerkushOnline_LobbyGM : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
};
