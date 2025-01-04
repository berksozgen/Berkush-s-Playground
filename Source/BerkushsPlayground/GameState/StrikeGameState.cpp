// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "StrikeGameState.h"

#include "BerkushsPlayground/PlayerState/StrikePlayerState.h"
#include "Net/UnrealNetwork.h"

void AStrikeGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AStrikeGameState, TopScoringPlayers);
}

void AStrikeGameState::UpdateTopScore(AStrikePlayerState* ScoringPlayer)
{
	if (TopScoringPlayers.Num() == 0)
	{
		TopScoringPlayers.Add(ScoringPlayer);
		TopScore = ScoringPlayer->GetScore();
	}
	else if (ScoringPlayer->GetScore() == TopScore)
	{
		TopScoringPlayers.AddUnique(ScoringPlayer);
	}
	else if (ScoringPlayer->GetScore() > TopScore)
	{
		TopScoringPlayers.Empty();
		TopScoringPlayers.Add(ScoringPlayer);
		TopScore = ScoringPlayer->GetScore();
	}
}