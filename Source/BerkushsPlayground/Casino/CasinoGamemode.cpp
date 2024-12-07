// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "CasinoGamemode.h"
#include "Card.h"
#include "CasinoPlayer.h"


ACasinoGamemode::ACasinoGamemode()
{
	PokerInitilizaer();

}

void ACasinoGamemode::PokerInitilizaer()
{
	ConstructorHelpers::FClassFinder<AActor> CardBPClass(TEXT("/Game/Casino/BP_Card"));
	if (!ensure(CardBPClass.Class != nullptr)) return;

	CardClass = CardBPClass.Class;
	
	
	ACard* CurrentCard;
	UWorld* World = GetWorld();

	if (World==nullptr) return;
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j < 15; j++)
		{
			CurrentCard = Cast<ACard>(World->SpawnActorDeferred<AActor>(CardClass, PokerTable));
			CurrentCard->CardSymbol = i;
			CurrentCard->CardPower = j;
			//CurrentCard->SetActorLabel(FString::Printf(TEXT("Poker Card = Symbol = %d, Power = %d"), i, j));
			CurrentCard->MyInitialize();
			PokerCards.Add(CurrentCard);
		}
	}
}

void ACasinoGamemode::PokerGame(TArray<class ACasinoPlayer*> Players, TArray<class AActor*> Cards)
{
	
}

AActor* ACasinoGamemode::Poker_WhoWinner(TArray<class ACasinoPlayer*> Players, TArray<class ACard*> DeskCards)
{
	TArray<FWinnerCardInfo> WinnersCardInfos;

	//Royal Flush Winner Check
	//Royal Flush Implementation End

	//Straight Flush Winner Check
	//Straight Flush Implementation End

	//Quad Winner Check
	//Quad Implementation End

	//Full House Winner Check
	//Full House Implementation End

	//Flush Winner Check
	//Flush Implementation End

	//Straight Winner Check
	//Straight Implementation End

	//Three of a Kind Winner Check
	//Three of a Kind Implementation End
	
	//Two Pair Winner Check
	//Two Pair Implementation End
	
	//Pair Winner Check
	//Pair Implementation End
	
	//High Card Winner Check
	for (int i = 0; i < Players.Num(); i++)
	{
		FWinnerCardInfo CurrentCardInfo = Poker_HighCard(Players[i]->PlayersHand);
		CurrentCardInfo.PlayerIndex = i;
		WinnersCardInfos.Add(CurrentCardInfo);
	}
	FWinnerCardInfo Winner = WinnersCardInfos[0];
	for (int i = 1; i < WinnersCardInfos.Num(); i++)
	{
		if (WinnersCardInfos[i].CardPower > Winner.CardPower)
		{
			Winner.CardPower=WinnersCardInfos[i].CardPower;
			Winner.CardSymbol=WinnersCardInfos[i].CardSymbol;
			Winner.PlayerIndex=WinnersCardInfos[i].PlayerIndex;
		}
		else if (WinnersCardInfos[i].CardPower == Winner.CardPower && WinnersCardInfos[i].CardSymbol > Winner.CardSymbol)
		{
			Winner.CardPower=WinnersCardInfos[i].CardPower;
			Winner.CardSymbol=WinnersCardInfos[i].CardSymbol;
			Winner.PlayerIndex=WinnersCardInfos[i].PlayerIndex;
		}
	}
	//High Card Implementation End
	return Players[Winner.PlayerIndex];
}

FWinnerCardInfo ACasinoGamemode::Poker_RoyalFlush(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards)
{
	return FWinnerCardInfo();
}
FWinnerCardInfo ACasinoGamemode::Poker_StraightFlush(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards)
{
	return FWinnerCardInfo();
}
FWinnerCardInfo ACasinoGamemode::Poker_Quad(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards)
{
	return FWinnerCardInfo();
}
FWinnerCardInfo ACasinoGamemode::Poker_FullHouse(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards)
{
	return FWinnerCardInfo();
}
FWinnerCardInfo ACasinoGamemode::Poker_Flush(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards)
{
	FWinnerCardInfo CardInfo;
	CardInfo.WinFunctionName = TEXT("Flush");
	if (PlayerCards[0]->CardSymbol == PlayerCards[1]->CardSymbol)
	{
		uint8 HowManyCardsWeNeed = 3;
		for (int i = 0; i < 5; i++)
		{
			if (PlayerCards[0]->CardSymbol == DeskCards[i]->CardSymbol)
			{
				--HowManyCardsWeNeed;
				if (HowManyCardsWeNeed <= 0)
				{
					if (PlayerCards[0]->CardPower > PlayerCards[1]->CardPower)
					{
						CardInfo.CardPower = PlayerCards[0]->CardPower;
						CardInfo.CardSymbol = PlayerCards[0]->CardSymbol;
						CardInfo.bIsWin = true;
						return CardInfo;
					}
					/*else*/
					{
						CardInfo.CardPower = PlayerCards[1]->CardPower;
						CardInfo.CardSymbol = PlayerCards[1]->CardSymbol;
						CardInfo.bIsWin = true;
						return CardInfo;
					}
				}
			}
		}
	}
	/*else*/
	{
		uint8 HowManyCardsWeNeedForFirstCard = 4;
		uint8 HowManyCardsWeNeedForSecondCard = 4;
		for (int i = 0; i < 5; i++)
		{
			if (PlayerCards[0]->CardSymbol == DeskCards[i]->CardSymbol)
			{
				HowManyCardsWeNeedForFirstCard--;
			}
			if (PlayerCards[1]->CardSymbol == DeskCards[i]->CardSymbol)
			{
				HowManyCardsWeNeedForSecondCard--;
			}
		}
		
		if (HowManyCardsWeNeedForFirstCard <= 0 && HowManyCardsWeNeedForSecondCard > 0)
		{
			CardInfo.CardPower = PlayerCards[0]->CardPower;
			CardInfo.CardSymbol = PlayerCards[0]->CardSymbol;
			CardInfo.bIsWin = true;
			return CardInfo;
		}
		/*else*/ if (HowManyCardsWeNeedForFirstCard > 0 && HowManyCardsWeNeedForSecondCard <= 0)
		{
			CardInfo.CardPower = PlayerCards[1]->CardPower;
			CardInfo.CardSymbol = PlayerCards[1]->CardSymbol;
			CardInfo.bIsWin = true;
			return CardInfo;
		}
		/*else*/ if (HowManyCardsWeNeedForFirstCard <= 0 && HowManyCardsWeNeedForSecondCard <= 0)
		{
			if(PlayerCards[0]->CardPower > PlayerCards[1]->CardPower)
			{
				CardInfo.CardPower = PlayerCards[0]->CardPower;
				CardInfo.CardSymbol = PlayerCards[0]->CardSymbol;
				CardInfo.bIsWin = true;
				return CardInfo;
			}
			/*else*/
			{
				CardInfo.CardPower = PlayerCards[1]->CardPower;
				CardInfo.CardSymbol = PlayerCards[1]->CardSymbol;
				CardInfo.bIsWin = true;
				return CardInfo;
			}
		}
		/*else*/
		{
			CardInfo.bIsWin = false;
			return CardInfo;
		}
	}
}
FWinnerCardInfo ACasinoGamemode::Poker_Straight(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards)
{
	FWinnerCardInfo CardInfo;
	CardInfo.WinFunctionName = TEXT("Straight");
	//Check Player Hand Can be Valid for Straight and they aren't same power
	uint8 PlayerCardsDifferance = FMath::Abs(PlayerCards[0]->CardPower - PlayerCards[1]->CardPower);
	if (PlayerCardsDifferance <= 4 && (PlayerCards[0]->CardPower - PlayerCards[1]->CardPower) != 0)
	{
		if(PlayerCardsDifferance == 1)
		{
			//Bu kartlar ardisik
			bool bThreeValueSmallerThanSmaller = false;
			bool bTwoValueSmallerThanSmaller = false;
			bool bOneValueSmallerThanSmaller = false;
			bool bOneValueGreaterThanGreater = false;
			bool bTwoValueGreaterThanGreater = false;
			bool bThreeValueGreaterThanGreater = false;

			uint8 PlayerBetterCardPower = Poker_ReturnHigherCard(PlayerCards[0], PlayerCards[1])->CardPower;
			uint8 ThreeValueSmallerCardPower = PlayerBetterCardPower - 4;
			uint8 TwoValueSmallerCardPower = PlayerBetterCardPower - 3;
			uint8 OneValueSmallerCardPower = PlayerBetterCardPower - 2;
			uint8 OneValueGreaterCardPower = PlayerBetterCardPower + 1;
			uint8 TwoValueGreaterCardPower = PlayerBetterCardPower + 2;
			uint8 ThreeValueGreaterCardPower = PlayerBetterCardPower + 3;

			for(int i = 0; i < 5; i++)
			{
				if(ThreeValueSmallerCardPower == DeskCards[i]->CardPower)
				{
					bThreeValueSmallerThanSmaller = true;
					continue;
				}
				if(TwoValueSmallerCardPower == DeskCards[i]->CardPower)
				{
					bTwoValueSmallerThanSmaller = true;
					continue;
				}
				if(OneValueSmallerCardPower == DeskCards[i]->CardPower)
				{
					bOneValueSmallerThanSmaller = true;
					continue;
				}
				if(OneValueGreaterCardPower == DeskCards[i]->CardPower)
				{
					bOneValueGreaterThanGreater = true;
					continue;
				}
				if(TwoValueGreaterCardPower == DeskCards[i]->CardPower)
				{
					bTwoValueGreaterThanGreater = true;
					continue;
				}
				if(ThreeValueGreaterCardPower == DeskCards[i]->CardPower)
				{
					bThreeValueGreaterThanGreater = true;
					continue;
				}
			}

			//Oyuncunun eline ek kazanma sartlari = 3 kucuk, 2 kucuk 1 buyuk, 1 kucuk 2 buyuk, 3 buyuk
			if(bThreeValueSmallerThanSmaller && bTwoValueSmallerThanSmaller && bOneValueSmallerThanSmaller)
			{
				return CardInfo;
			}
			if(bTwoValueSmallerThanSmaller && bOneValueSmallerThanSmaller && bOneValueGreaterThanGreater)
			{
				return CardInfo;
			}
			if(bOneValueSmallerThanSmaller && bOneValueGreaterThanGreater && bTwoValueGreaterThanGreater)
			{
				return CardInfo;
			}
			if(bOneValueGreaterThanGreater && bTwoValueGreaterThanGreater && bThreeValueGreaterThanGreater)
			{
				return CardInfo;
			}
			//Demekki kent yok puhaha
			return CardInfo;
		}
		/*else*/ if (PlayerCardsDifferance == 2)
		{
			//Aralarinda bir kart var, onun degerini bul
			uint8 BetweenCardPower = (PlayerCards[0]->CardPower + PlayerCards[1]->CardPower) / 2;
			bool bIsThereBetweenCard = false;
			for(int i = 0; i < 5; i++)
			{
				if(BetweenCardPower == DeskCards[i]->CardPower)
				{
					bIsThereBetweenCard = true;
					break;
				}
			}
			if (!bIsThereBetweenCard)
			{
				CardInfo.bIsWin = false;
				return CardInfo;
			}
			//Aralarinda bir kart var, kalan senaryolar = kucukten 2 kucuk, buyukten 2 buyuk, kucukten 1 kucuk ve buyukten 1 buyuk
			bool bTwoValueSmallerThanSmaller = false;
			bool bOneValueSmallerThanSmaller = false;
			bool bOneValueGreaterThanGreater = false;
			bool bTwoValueGreaterThanGreater = false;

			uint8 TwoValueSmallerCardPower = BetweenCardPower - 3;
			uint8 OneValueSmallerCardPower = BetweenCardPower - 2;
			uint8 OneValueGreaterCardPower = BetweenCardPower + 2;
			uint8 TwoValueGreaterCardPower = BetweenCardPower + 3;
			
			for(int i = 0; i < 5; i++)
			{
				if(TwoValueSmallerCardPower == DeskCards[i]->CardPower)
				{
					bTwoValueSmallerThanSmaller = true;
					continue;
				}
				if(OneValueSmallerCardPower == DeskCards[i]->CardPower)
				{
					bOneValueSmallerThanSmaller = true;
					continue;
				}
				if(OneValueGreaterCardPower == DeskCards[i]->CardPower)
				{
					bOneValueGreaterThanGreater = true;
					continue;
				}
				if(TwoValueGreaterCardPower == DeskCards[i]->CardPower)
				{
					bTwoValueGreaterThanGreater = true;
					continue;
				}
			}
			
			if(bTwoValueSmallerThanSmaller && bOneValueSmallerThanSmaller)
			{
				//Oyuncunun elindeki buyuk card buyuk
				CardInfo.bIsWin = true;
				CardInfo.CardPower = Poker_ReturnHigherCard(PlayerCards[0], PlayerCards[1])->CardPower;
				CardInfo.CardSymbol = Poker_ReturnHigherCard(PlayerCards[0], PlayerCards[1])->CardPower;
				return CardInfo;
			}
			if (bOneValueSmallerThanSmaller && bOneValueGreaterThanGreater)
			{
				//Masada Kent'i tamamlayan, oyununun elindeki buyuk karttan 1 degerli olan card buyuk
				CardInfo.bIsWin = true;
				for(int i = 0; i < 5; i++)
				{
					if (OneValueGreaterCardPower == DeskCards[i]->CardPower)
					{
						CardInfo.CardPower = DeskCards[i]->CardPower;
						CardInfo.CardSymbol = DeskCards[i]->CardSymbol;
						break;
					}
				}
				return CardInfo;
			}
			if (bOneValueGreaterThanGreater && bTwoValueGreaterThanGreater)
			{
				//Masada Kent'i tamalayan, oyuncunun elindeki karttan 2 degerli olan kart buyuk
				CardInfo.bIsWin = true;
				for(int i = 0; i < 5; i++)
				{
					if (TwoValueGreaterCardPower == DeskCards[i]->CardPower)
					{
						CardInfo.CardPower = DeskCards[i]->CardPower;
						CardInfo.CardSymbol = DeskCards[i]->CardSymbol;
						break;
					}
				}
				return CardInfo;
			}
			//Oyuncu Kent yapamadi
			CardInfo.bIsWin = false;
			return CardInfo;
		}
		/*else*/ if(PlayerCardsDifferance == 3)
		{
			return CardInfo;
		}
		/*else*/ if(PlayerCardsDifferance == 4)
		{
			return CardInfo;
		}
		else // default
		{
			return CardInfo;
		}
	}
	/*else*/ // Player Hand Wasn't valid for straight (or he has same powered cards), check 2 cards separately
	{
		if ((PlayerCards[0]->CardPower - PlayerCards[1]->CardPower) == 0) //Player has same powered card
		{
			ACard* BetterCard = Poker_ReturnHigherCard(PlayerCards[0], PlayerCards[1]);
			//Do something
			return CardInfo;
		}
		/*else*/ //Check 2 Cards Separately
		{
			//Do more thing
			return CardInfo;
		}
	}
}
FWinnerCardInfo ACasinoGamemode::Poker_ThreeOfAKind(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards)
{
	FWinnerCardInfo CardInfo;
	CardInfo.WinFunctionName = TEXT("Three of a Kind");
	if (PlayerCards[0]->CardPower == PlayerCards[1]->CardPower)
	{
		for (int i = 0; i < 5; i++)
		{
			if (PlayerCards[0]->CardPower == DeskCards[i]->CardPower)
			{
				CardInfo.CardPower = PlayerCards[0]->CardPower;
				CardInfo.CardSymbol = PlayerCards[0]->CardSymbol;
				return CardInfo;
			}
		}
	}
	/*else*/
	{
		uint8 FirstCardPairCount = 0;
		for (int i = 0; i < 5; i++)
		{
			if (PlayerCards[0]->CardPower == DeskCards[i]->CardPower)
			{
				FirstCardPairCount++;
			}
		}
		uint8 SecondCardPairCount = 0;
		for (int i = 0; i < 5; i++)
		{
			if (PlayerCards[1]->CardPower == DeskCards[i]->CardPower)
			{
				SecondCardPairCount++;
			}
		}
		if (FirstCardPairCount >= 2 && SecondCardPairCount < 2)
		{
			CardInfo.CardPower = PlayerCards[0]->CardPower;
			CardInfo.CardSymbol = PlayerCards[0]->CardSymbol;
			CardInfo.bIsWin = true;
			return CardInfo;
		}
		/*else*/ if (FirstCardPairCount < 2 && SecondCardPairCount >= 2)
		{
			CardInfo.CardPower = PlayerCards[1]->CardPower;
			CardInfo.CardSymbol = PlayerCards[1]->CardSymbol;
			CardInfo.bIsWin = true;
			return CardInfo;
		}
		/*else*/ if (FirstCardPairCount >= 2 && SecondCardPairCount >= 2)
		{
			if(PlayerCards[0]->CardPower > PlayerCards[1]->CardPower)
			{
				CardInfo.CardPower = PlayerCards[0]->CardPower;
				CardInfo.CardSymbol = PlayerCards[0]->CardSymbol;
				CardInfo.bIsWin = true;
				return CardInfo;
			}
			/*else*/
			{
				CardInfo.CardPower = PlayerCards[1]->CardPower;
				CardInfo.CardSymbol = PlayerCards[1]->CardSymbol;
				CardInfo.bIsWin = true;
				return CardInfo;
			}
		}
		/*else*/
		{
			CardInfo.bIsWin = false;
			return CardInfo;
		}
	}
}
FWinnerCardInfo ACasinoGamemode::Poker_TwoPair(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards)
{
	FWinnerCardInfo CardInfo;
	CardInfo.WinFunctionName = TEXT("Two Pair");
	CardInfo.bIsWin = false;
	bool bHasFirstCardHasPair = false;
	for (int i = 0; i < 5; i++)
	{
		if (PlayerCards[0]->CardPower == DeskCards[i]->CardPower)
		{
			bHasFirstCardHasPair = true;
			break;
		}
	}
	if (!bHasFirstCardHasPair) return CardInfo;
	for (int i = 0; i < 5; i++)
	{
		if (PlayerCards[1]->CardPower == DeskCards[i]->CardPower)
		{
			CardInfo.bIsWin = true;
			return CardInfo;
		}
	}
	return CardInfo;
}
FWinnerCardInfo ACasinoGamemode::Poker_Pair(TArray <class ACard*> PlayerCards, TArray<class ACard*> DeskCards)
{
	FWinnerCardInfo CardInfo;
	CardInfo.WinFunctionName = TEXT("Pair");
	//Player Has Pair On His Hand
	if (PlayerCards[0]->CardPower == PlayerCards[1]->CardPower)
	{
		CardInfo.CardPower = PlayerCards[0]->CardPower;
		CardInfo.CardSymbol = PlayerCards[0]->CardSymbol;
		if (PlayerCards[1]->CardSymbol > PlayerCards[0]->CardSymbol)
		{
			CardInfo.CardSymbol = PlayerCards[1]->CardSymbol;
		}
		return CardInfo;
	}
	//Check Player Has Pair With Desk
	bool bIsCardZeroHasPair = false;
	for (int i = 0; i < 5; i++)
	{
		if (DeskCards[i]->CardPower==PlayerCards[0]->CardPower) bIsCardZeroHasPair = true;
	}
	bool bIsCardOneHasPair = false;
	for (int i = 0; i < 5; i++)
	{
		if (DeskCards[i]->CardPower==PlayerCards[1]->CardPower) bIsCardOneHasPair = true;
	}
	if (bIsCardZeroHasPair)
	{
		if (!bIsCardOneHasPair)
		{
			CardInfo.CardPower = PlayerCards[0]->CardPower;
			CardInfo.CardSymbol = PlayerCards[0]->CardSymbol;
			return CardInfo;
		}
		/*else*/
		{
			if (PlayerCards[1]->CardPower > CardInfo.CardPower)
			{
				CardInfo.CardPower = PlayerCards[1]->CardPower;
				CardInfo.CardSymbol = PlayerCards[1]->CardSymbol;
				return CardInfo;
			}
			/*else*/ if (PlayerCards[1]->CardPower == CardInfo.CardPower)
			{
				if (PlayerCards[1]->CardSymbol > CardInfo.CardSymbol)
				{
					CardInfo.CardPower = PlayerCards[1]->CardPower;
					CardInfo.CardSymbol = PlayerCards[1]->CardSymbol;
					return CardInfo;
				}
				/*else*/
				{
					CardInfo.CardPower = PlayerCards[0]->CardPower;
					CardInfo.CardSymbol = PlayerCards[0]->CardSymbol;
					return CardInfo;
				}
			}
		}
	}
	/*else*/
	{
		if (bIsCardOneHasPair)
		{
			CardInfo.CardPower = PlayerCards[1]->CardPower;
			CardInfo.CardSymbol = PlayerCards[1]->CardSymbol;
			return CardInfo;
		}
		/*else*/
		{
			CardInfo.bIsWin = false;
			return CardInfo;
		}
	}
}
FWinnerCardInfo ACasinoGamemode::Poker_HighCard(TArray <class ACard*> PlayerCards)
{
	FWinnerCardInfo CardInfo;
	CardInfo.WinFunctionName = TEXT("High Card");
	CardInfo.CardPower=PlayerCards[0]->CardPower;
	CardInfo.CardSymbol=PlayerCards[0]->CardSymbol;
	if (PlayerCards[1]->CardPower > CardInfo.CardPower)
	{
		CardInfo.CardPower=PlayerCards[1]->CardPower;
		CardInfo.CardSymbol=PlayerCards[1]->CardSymbol;
	}
	else if (PlayerCards[1]->CardPower == CardInfo.CardPower && PlayerCards[1]->CardSymbol > CardInfo.CardSymbol)
	{
		CardInfo.CardPower=PlayerCards[1]->CardPower;
		CardInfo.CardSymbol=PlayerCards[1]->CardSymbol;
	}
	return CardInfo;
}

ACard* ACasinoGamemode::Poker_ReturnHigherCard(class ACard* Card1, class ACard* Card2)
{
	if (Card1->CardPower > Card2->CardPower) return Card1;
	if (Card2->CardPower > Card1->CardPower) return Card2;
	if (Card1->CardSymbol > Card2->CardSymbol) return Card1;
	return Card2;
}