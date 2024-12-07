// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/TextRenderComponent.h"

#include "Card.generated.h"

static TArray<FString> CardFrontImages = { "🃒","🃓","🃔","🃕","🃖","🃗","🃘","🃙","🃚","🃛","🃝","🃞","🃑", /*Sinek*/
									"🂢","🂣","🂤","🂥","🂦","🂧","🂨","🂩","🂪","🂫","🂭","🂮","🂡", /*Maca*/
									"🃂","🃃","🃄","🃅","🃆","🃇","🃈","🃉","🃊","🃋","🃍","🃎","🃁", /*Karo*/
									"🂲","🂳","🂴","🂵","🂶","🂷","🂸","🂹","🂺","🂻","🂽","🂾","🂱" }; /*Kupa*/

static TArray<FString> CardSymbols = {"Sinek","Maca","Karo","Kupa"};


UCLASS()
class BERKUSHSPLAYGROUND_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACard();

	void MyInitialize();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta =(ExposeOnSpawn = true))
	uint8 CardSymbol;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta =(ExposeOnSpawn = true))
	uint8 CardPower;

	UPROPERTY(BlueprintReadWrite)
	UTextRenderComponent* CardDemoText;

	UPROPERTY(BlueprintReadWrite)
	FString CardFrontImage;
	UPROPERTY(BlueprintReadOnly)
	FString CardBackImage = TEXT("🂠");


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
