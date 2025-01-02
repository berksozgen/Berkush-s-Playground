// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "StrikePlayerController.h"
#include "BerkushsPlayground/HUD/StrikeHUD.h"
#include "BerkushsPlayground/HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void AStrikePlayerController::BeginPlay()
{
	Super::BeginPlay();

	 StrikeHUD = Cast<AStrikeHUD>(GetHUD());
}

void AStrikePlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	StrikeHUD = StrikeHUD == nullptr ? Cast<AStrikeHUD>(GetHUD()) : StrikeHUD;

	bool bHUDValid = StrikeHUD && StrikeHUD->CharacterOverlay && StrikeHUD->CharacterOverlay->HealthBar && StrikeHUD->CharacterOverlay->HealthText; //siralama onemli btw
	if (bHUDValid)
	{
		const float HealthPercent = Health / MaxHealth;
		StrikeHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		FString HealthText = FString::Printf(TEXT("%c%d"), '%', FMath::CeilToInt(100.f * HealthPercent));
		StrikeHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}