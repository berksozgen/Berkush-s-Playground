// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "Card.h"

// Sets default values
ACard::ACard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
	CardFront = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CardFront"));
	CardFront->SetupAttachment(GetRootComponent());
	CardBack = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CardBack"));
	CardBack->SetupAttachment(GetRootComponent());
}

void ACard::MyInitialize()
{
	SetActorLabel(FString::Printf(TEXT("Card Symbol = %d, Power = %d"), CardSymbol, CardPower));
	SetReplicates(true);
	SetReplicateMovement(true);
}


// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

