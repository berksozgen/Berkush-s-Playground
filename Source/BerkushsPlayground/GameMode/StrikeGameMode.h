// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StrikeGameMode.generated.h"

namespace MatchState
{
	extern BERKUSHSPLAYGROUND_API const FName Cooldown; // Match duration has been reached. Display winner and begin cooldown timer.
}

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API AStrikeGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AStrikeGameMode();
	virtual void Tick(float DeltaSeconds) override; //buna ihtiyacim olmayabilir
	virtual void PlayerEliminated(class AStrikeCharacter* ElimmedCharacter, class AStrikePlayerController* VictimController, AStrikePlayerController* AttackerController);
	virtual void RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController);

	UPROPERTY(EditDefaultsOnly, Category = "Time")
	float MatchTime = 120.f;
	UPROPERTY(EditDefaultsOnly, Category = "Time")
	float WarmupTime = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = "Time")
	float CooldownTime = 10.f;

	float LevelStartingTime = 0.f;

protected:
	virtual void BeginPlay() override;
	virtual void OnMatchStateSet() override;
private:
	float CountdownTime = 0.f;
public:
	FORCEINLINE float GetCountdownTime() const { return CountdownTime; }
};
