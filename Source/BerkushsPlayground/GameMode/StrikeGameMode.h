// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StrikeGameMode.generated.h"

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
	float WarmupTime = 10.f;

	float LevelStartingTime = 0;

protected:
	virtual void BeginPlay() override;
private:
	float CountdownTime = 0.f;
};
