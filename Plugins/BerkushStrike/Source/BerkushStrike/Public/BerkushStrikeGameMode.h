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
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	UFUNCTION(BlueprintCallable, Category = "BerkushStrike")
	void AvatarsOverlapped(class UBerkushStrikePlayerComponent* PlayerA, class UBerkushStrikePlayerComponent* PlayerB); // Biri oldu dye degisirim bunu

	UFUNCTION(BlueprintCallable, Category = "BerkushStrike")
	void EndGame();

	//virtual void OnPostLogin(AController* NewPlayer) override;

private:

	int TotalPlayerCount;
	int TotalGames;
	int PlayerStartIndex;

	TArray<APlayerController*> AllPlayers;

	AActor* GetPlayerStart(FString Name, int Index);

	AActor* AssignTeamAndPlayerStart(AController* Player);
	
};
