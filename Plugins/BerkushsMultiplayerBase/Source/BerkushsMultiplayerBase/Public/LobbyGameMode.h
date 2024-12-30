// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSMULTIPLAYERBASE_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void PostLogin(APlayerController* NewPlayer) override;

	void Logout(AController* Exiting) override;

	UFUNCTION(BlueprintCallable, Category = "Berkush's Multiplayer Base")
	void StartGame(FString MapPath);
	
private:

	FTimerHandle GameStartTimer;

	uint32 NumberOfPlayers = 0;
	
};
//push comment