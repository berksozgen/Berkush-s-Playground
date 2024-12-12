// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "BerkushsPlayground//MultiplayerGameMode.h"
#include "CasinoGamemode.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWinnerCardInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool bIsWin = false;
	UPROPERTY()
	uint8 CardPower = 0;
	UPROPERTY()
	uint8 CardSymbol = 0;
	UPROPERTY()
	uint8 PlayerIndex = 0;
	UPROPERTY()
	FString WinFunctionName = TEXT("Error!");
};

UCLASS()
class BERKUSHSPLAYGROUND_API ACasinoGamemode : public AMultiplayerGameMode
{
	GENERATED_BODY()

	ACasinoGamemode();

public:
	virtual void BeginPlay() override;

	public:
	TSubclassOf<class AActor> CardClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform DeckSpawnPosition;
	
	void PokerGame(TArray<class ACasinoPlayer*> Players, TArray<class AActor*> Cards); //Bu burada mi olmali cozemedim

	UFUNCTION(NetMulticast, Reliable)
	void MultiCast_PokerInitilizaer();


private:
	
	TArray<class ACard*> PokerCards;
	

	AActor* Poker_WhoWinner(TArray<class ACasinoPlayer*> Players, TArray<class ACard*> DeskCards);

	static FWinnerCardInfo Poker_RoyalFlush(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_StraightFlush(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Quad(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_FullHouse(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Flush(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Straight_Individual_Checker(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Straight_Individual(class ACard* PlayerCard, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Straight(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static TArray<class ACard*> Poker_Straight_Array(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_ThreeOfAKind_Individual(class ACard* PlayerCard, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_ThreeOfAKind(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_TwoPair(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Pair_Individual(ACard* PlayerCard, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Pair(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_HighCard(TArray <class ACard*> PlayerCards);
	static class ACard* Poker_ReturnHigherCard(class ACard* Card1, class ACard* Card2);
};
