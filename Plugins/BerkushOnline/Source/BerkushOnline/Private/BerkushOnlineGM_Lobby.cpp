// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "BerkushOnlineGM_Lobby.h"

#include "BerkushOnlineSubsystem.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ABerkushOnlineGM_Lobby::PostLogin(APlayerController* NewPlayer) //This is the first place to Call Replicated Functions on the Player Controller
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

	if(GEngine) //Key mantiginin olayi, ayni keyde bir mesajdaha gonderince oncekinin ustune yaziyor
	{
		GEngine->AddOnScreenDebugMessage(
			1,
			60.f,
			FColor::Yellow,
			FString::Printf(TEXT("Players in game: %d"),NumberOfPlayers));

		APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
		if(PlayerState)
		{
			FString PlayerName = PlayerState->GetPlayerName();
			GEngine->AddOnScreenDebugMessage(
				-1,
				60.f,
				FColor::Cyan,
				FString::Printf(TEXT("%s has joined the game!"),*PlayerName));
		}
	}
	
	if(NumberOfPlayers == 2)
	{
		UWorld* World = GetWorld();
		if(World)
		{
			bUseSeamlessTravel = true;
			World->ServerTravel(FString("/Game/Maps/FastPaced/Poolday/MAP_Poolday?listen"));
		}
	}
}

void ABerkushOnlineGM_Lobby::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (GEngine && GameState)
	{
		APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
		if(PlayerState)
		{
			int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Players in game: %d"),NumberOfPlayers - 1)); //Burada number of players updatelenmemis oluyor
		
			FString PlayerName = PlayerState->GetPlayerName();
			GEngine->AddOnScreenDebugMessage(
				-1,
				60.f,
				FColor::Red,
				FString::Printf(TEXT("%s has exiting the game!"),*PlayerName));
		}
	}
}

void ABerkushOnlineGM_Lobby::StartGame(FString MapPath)
{
	
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		auto MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UBerkushOnlineSubsystem>();
		if (MultiplayerSessionsSubsystem == nullptr) return;

		//MultiplayerSessionsSubsystem->StartSession(); //Implemente degil Gerek de yok gerci
	
		UWorld* World = GetWorld();
		if (!ensure(World!=nullptr)) return;

		bUseSeamlessTravel = true;
		World->ServerTravel( FString::Printf(TEXT("%s?listen"),*MapPath));
	}
}


