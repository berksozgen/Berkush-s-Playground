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
	UPROPERTY(BlueprintReadWrite)
	FTransform PokerTable;

	TSubclassOf<class AActor> CardClass;

	TArray<class ACard*> PokerCards;

	void PokerInitilizaer();
	void PokerGame(TArray<class ACasinoPlayer*> Players, TArray<class AActor*> Cards);

	AActor* Poker_WhoWinner(TArray<class ACasinoPlayer*> Players, TArray<class ACard*> DeskCards);

	static FWinnerCardInfo Poker_RoyalFlush(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_StraightFlush(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Quad(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_FullHouse(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Flush(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Straight(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_ThreeOfAKind(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_TwoPair(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_Pair(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards);
	static FWinnerCardInfo Poker_HighCard(TArray <class ACard*> PlayerCards);
	static class ACard* Poker_ReturnHigherCard(class ACard* Card1, class ACard* Card2);
};
