// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BerkushOnlineGM_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHONLINE_API ABerkushOnlineGM_Lobby : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	
	UFUNCTION(BlueprintCallable, Category = "BerkushOnline|Lobby")
	void StartGame(FString MapPath);
};
