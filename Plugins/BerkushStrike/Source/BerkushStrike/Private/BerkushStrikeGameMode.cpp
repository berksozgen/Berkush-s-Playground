// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "BerkushStrikeGameMode.h"

#include "BerkushStrikeGameHandler.h"
#include "BerkushStrikeGameState.h"
#include "BerkushStrikePlayerComponent.h"
#include "BerkushStrikePlayerState.h"
#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ABerkushStrikeGameMode::ABerkushStrikeGameMode()
{
	//PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_BerkushsLALSCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerStateClass = ABerkushStrikePlayerState::StaticClass();
	GameStateClass = ABerkushStrikeGameState::StaticClass();
	
}

AActor* ABerkushStrikeGameMode::GetPlayerStart(FString Name, int Index)
{
	FName PSName = (Index < 0) ? *Name : *FString::Printf(TEXT("%s%d"), *Name, Index % 4);

	for (TActorIterator<APlayerStart> It (GWorld); It; ++It)
	{
		if(APlayerStart* PS = Cast<APlayerStart>(*It))
		{
			if(PS->PlayerStartTag == PSName) return *It;
		}
	}

	return nullptr;
}

AActor* ABerkushStrikeGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	AActor* Start = nullptr;
	ABerkushStrikePlayerState* PlayerState = Player->GetPlayerState<ABerkushStrikePlayerState>();
	if (PlayerState)
	{
		if(TotalGames == 0)
		{
			PlayerState->PlayerTeam = TotalPlayerCount == 0 ? EBerkushStrikePlayerTeam::Blue : EBerkushStrikePlayerTeam::Red;
			PlayerState->PlayerIndex = TotalPlayerCount++;
			AllPlayers.Add(Cast<APlayerController>(Player));
		}
		else PlayerState->PlayerTeam = PlayerState->Result == EBerkushStrikeRoundResults::Won ? EBerkushStrikePlayerTeam::Blue : EBerkushStrikePlayerTeam::Red;

		Start = (PlayerState->PlayerTeam == EBerkushStrikePlayerTeam::Blue) ? GetPlayerStart("Blue", -1) : GetPlayerStart("Red", PlayerStartIndex++);
	}
	return Start;
}

void ABerkushStrikeGameMode::AvatarsOverlapped(UBerkushStrikePlayerComponent* PlayerA, UBerkushStrikePlayerComponent* PlayerB)
{
	ABerkushStrikeGameState* GameState = GetGameState<ABerkushStrikeGameState>();
	if (GameState==nullptr || GameState->WinningPlayer >=0) return;
	
	ACharacter* PlayerAChr = Cast<ACharacter>(PlayerA->GetOwner());
	ACharacter* PlayerBChr = Cast<ACharacter>(PlayerB->GetOwner());

	ABerkushStrikePlayerState* PStateA = PlayerAChr->GetPlayerState<ABerkushStrikePlayerState>();
	ABerkushStrikePlayerState* PStateB = PlayerBChr->GetPlayerState<ABerkushStrikePlayerState>();

	GameState->WinningPlayer = (PStateA->PlayerTeam == EBerkushStrikePlayerTeam::Red) ? PStateA->PlayerIndex : PStateB->PlayerIndex;


	PlayerAChr->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore); //Bunlari Cast Etmek gerekibiir
	PlayerBChr->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	GameState->OnVictory();

	for (APlayerController* Player : AllPlayers)
	{
		auto PState = Player->GetPlayerState<ABerkushStrikePlayerState>();

		PState->Result = (PState->PlayerTeam == EBerkushStrikePlayerTeam::Blue) ? EBerkushStrikeRoundResults::Lost : EBerkushStrikeRoundResults::Won;
	}

	FTimerHandle EndGameTimerHandle;
	GWorld->GetTimerManager().SetTimer(EndGameTimerHandle, this, &ABerkushStrikeGameMode::EndGame, 2.5f, false);
}

void ABerkushStrikeGameMode::EndGame()
{
	PlayerStartIndex = 0;
	TotalGames++;
	GetGameState<ABerkushStrikeGameState>()->WinningPlayer = -1;

	for(APlayerController* Player : AllPlayers)
	{
		APawn* Pawn = Player->GetPawn();
		Player->UnPossess();
		Pawn->Destroy();
		Player->StartSpot.Reset();
		RestartPlayer(Player);
	}

	ABerkushStrikeGameState* GameState = GetGameState<ABerkushStrikeGameState>();
	GameState->TriggerRestart();
}



/*
void ABerkushStrikeGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	APawn* PlayerPawn = GWorld->SpawnActor<APawn>(PlayerPawnClass);
	NewPlayer->GetPawn()->AddComponentByClass(UBerkushStrikePlayerComponent::StaticClass(),false,FTransform::Identity,false);


	ABerkushStrikeGameHandler* GameHandler = Cast<ABerkushStrikeGameHandler>(UGameplayStatics::GetActorOfClass(GWorld,ABerkushStrikeGameHandler::StaticClass()));
	FTransform SpawnPosition = GameHandler->GiveSpawnLocation(Cast<class UBerkushStrikePlayerComponent>(PlayerPawn->GetComponentByClass(UBerkushStrikePlayerComponent::StaticClass())));
	PlayerPawn->SetActorTransform(SpawnPosition);
	}
*/