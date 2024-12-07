// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "Card.h"

// Sets default values
ACard::ACard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
	CardDemoText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CardDemoText"));
}

void ACard::MyInitialize()
{
	//CardFrontImage = CardFrontImages[(CardSymbol*13)+CardSymbol];
	CardDemoText->SetText(FText::FromString(FString::Printf(TEXT("%s %d"),*CardSymbols[CardSymbol],CardPower)));
	//SetActorLabel(FString::Printf(TEXT("Poker Card = Symbol = %d, Power = %d"), CardSymbol, CardPower));
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

