// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "StrikePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API AStrikePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	/*Replication Notifies*/
	virtual void OnRep_Score() override;
	UFUNCTION()
	void OnRep_Kills();
	UFUNCTION()
	void OnRep_Deaths();
	
	void AddToScore(float ScoreAmount);
	void AddToKills(int32 KillsAmount);
	void AddToDeaths(int32 DeathsAmount);
protected:
	
private:
	UPROPERTY()
	class AStrikeCharacter* Character; /*UPROPERTY makrosu null ptr ile baslatiyormus variablelari*/
	UPROPERTY()
	class AStrikePlayerController* Controller;
	UPROPERTY(ReplicatedUsing=OnRep_Kills)
	int32 Kills;
	UPROPERTY(ReplicatedUsing=OnRep_Deaths)
	int32 Deaths;

};
