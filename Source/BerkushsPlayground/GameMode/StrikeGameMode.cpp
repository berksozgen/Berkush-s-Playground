// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "StrikeGameMode.h"
#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "BerkushsPlayground/PlayerController/StrikePlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "BerkushsPlayground/PlayerState/StrikePlayerState.h"

void AStrikeGameMode::PlayerEliminated(AStrikeCharacter* ElimmedCharacter,
                                       AStrikePlayerController* VictimController, AStrikePlayerController* AttackerController)
{
	AStrikePlayerState* AttackerPlayerState = AttackerController ? Cast<AStrikePlayerState>(AttackerController->PlayerState/*niye get player state kullanmadik ki*/) : nullptr;
	AStrikePlayerState* VictimPlayerState = VictimController ? Cast<AStrikePlayerState>(VictimController->PlayerState) : nullptr;

	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState)
	{
		AttackerPlayerState->AddToScore(14.07f);
		AttackerPlayerState->AddToKills(1);
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddToDeaths(1);
	}
	if (VictimController) VictimController->SetHUDKilledText(FString(TEXT("You Have Been Killed!")));
	
	if (ElimmedCharacter) ElimmedCharacter->Elim();
}

void AStrikeGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Reset(); //Destroy atmadan bunu cagirma nedenimiz Datalari kaybolmasin diye
		ElimmedCharacter->Destroy();
	}
	if (ElimmedController)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts); //He bunlar statik fonksiyon oldugu icin world'u weya world context objelerini istiyormus, aydinlandim ak
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(ElimmedController, PlayerStarts[Selection]); /*BTW respawn atarken oldugu yere en yakin olani/diger oyunculardan en uzak olani veya takimsal mantikla yapabilirim, gene aydinlandim*/
	}
}