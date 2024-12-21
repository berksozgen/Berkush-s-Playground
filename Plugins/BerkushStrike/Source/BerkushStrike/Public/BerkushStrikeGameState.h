// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "FireArmBase.h"
#include "GameFramework/GameState.h"
#include "BerkushStrikeGameState.generated.h"

UENUM(BlueprintType, Category = "BerkushStrike")
enum class EBerkushStrikeGameModeType : uint8
{
	DeathMatch,
	Bomb,
	ArmsRace,
	Sniper,
};

/**
 * 
 */
UCLASS()
class BERKUSHSTRIKE_API ABerkushStrikeGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	int32 BlueTeamAlivePlayers = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	int32 RedTeamAlivePlayers = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	int32 BlueTeamScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	int32 RedTeamScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	int32 RemainingType = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	EBerkushStrikeGameModeType GameModeType = EBerkushStrikeGameModeType::DeathMatch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	TArray<AFireArmBase*> SpawnGuns;
	
};
