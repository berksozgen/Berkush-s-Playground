// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BerkushStrikePlayerComponent.h"
#include "BerkushStrikePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSTRIKE_API ABerkushStrikePlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "BerkushStrike")
	int PlayerIndex;

	EBerkushStrikePlayerTeam PlayerTeam;
	EBerkushStrikeRoundResults Result;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	
	
};
