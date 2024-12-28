// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "BerkushStrikeGameHandler.h"

#include "GameFramework/Pawn.h"

#include "BerkushStrikePlayerComponent.h"
#include "MovieSceneTracksComponentTypes.h"
#include "Components/BoxComponent.h"

// Sets default values
ABerkushStrikeGameHandler::ABerkushStrikeGameHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_BerkushsLALSCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		PlayerClass = PlayerPawnBPClass.Class;
	}

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComponent);
	RedTeamSpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("RedTeamSpawnArea"));
	RedTeamSpawnArea->SetupAttachment(RootComponent);
	BlueTeamSpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("BlueTeamSpawnArea"));
	BlueTeamSpawnArea->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABerkushStrikeGameHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABerkushStrikeGameHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
FTransform ABerkushStrikeGameHandler::GiveSpawnLocation(UBerkushStrikePlayerComponent* BerkushStrikeComponent)
{
	FTransform ReturnTransform = FTransform::Identity;
	if(BerkushStrikeComponent->PlayerTeam == EBerkushStrikePlayerTeam::Spectator) return  ReturnTransform;

	FBoxSphereBounds Bounds;
	if (BerkushStrikeComponent->PlayerTeam == EBerkushStrikePlayerTeam::Red)
	{
		Bounds = RedTeamSpawnArea->Bounds;
		FBox Box = Bounds.GetBox();
		ReturnTransform.SetLocation(FMath::RandPointInBox(Box));
	}
	else
	{
		Bounds = BlueTeamSpawnArea->Bounds;
		FBox Box = Bounds.GetBox();
		ReturnTransform.SetLocation(FMath::RandPointInBox(Box));
	}
	return ReturnTransform;
}
*/

