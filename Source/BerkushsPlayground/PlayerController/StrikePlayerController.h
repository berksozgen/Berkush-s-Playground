// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StrikePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API AStrikePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDKills(int32 Kills);
	void SetHUDDeaths(int32 Deaths);
	void SetHUDKilledText(FString KilledText);
	virtual void OnPossess(APawn* InPawn) override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	class AStrikeHUD* StrikeHUD;
	
};
