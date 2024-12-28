// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "BerkushStrikeGameMode.h"

#include "BerkushStrikeGameHandler.h"
#include "BerkushStrikePlayerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ABerkushStrikeGameMode::ABerkushStrikeGameMode()
{
	//PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_BerkushsLALSCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		PlayerPawnClass = PlayerPawnBPClass.Class;
	} 
	
}

void ABerkushStrikeGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	/*
	APawn* PlayerPawn = GWorld->SpawnActor<APawn>(PlayerPawnClass);
	NewPlayer->GetPawn()->AddComponentByClass(UBerkushStrikePlayerComponent::StaticClass(),false,FTransform::Identity,false);
	*/
	/*
	ABerkushStrikeGameHandler* GameHandler = Cast<ABerkushStrikeGameHandler>(UGameplayStatics::GetActorOfClass(GWorld,ABerkushStrikeGameHandler::StaticClass()));
	FTransform SpawnPosition = GameHandler->GiveSpawnLocation(Cast<class UBerkushStrikePlayerComponent>(PlayerPawn->GetComponentByClass(UBerkushStrikePlayerComponent::StaticClass())));
	PlayerPawn->SetActorTransform(SpawnPosition);
	*/
}