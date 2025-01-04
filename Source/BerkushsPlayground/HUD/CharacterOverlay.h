// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterOverlay.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API UCharacterOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreAmount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillsAmount;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathsAmount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KilledText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponAmmoAmount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CarriedAmmoAmount;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponAmmoType;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MatchCountdownText;
};
