// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "StrikeGameState.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API AStrikeGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void UpdateTopScore(class AStrikePlayerState* ScoringPlayer);
	
	UPROPERTY(Replicated)
	TArray<AStrikePlayerState*> TopScoringPlayers;
protected:

private:
	float TopScore = 0.f;
};