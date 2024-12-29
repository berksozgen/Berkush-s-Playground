// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
/*Other Headers*/
#include "Interfaces/OnlineSessionInterface.h"

//
#include "BerkushOnlineSubsystem.generated.h"
/*Don't forget the implementing StartSessions, Actually I don't need this, if i start session, players cannot join in progress i guess (Like L4D2)*/
//
//Declaring our own custom delegates for the Menu class to bind callbacks to
//

/*
 * Delegeler Hakkinda Notlarim
 * Multicast, bu bir kere broadcas yapildiginda?, birden fazla Sinif buna uye olup callback alabiliyor (Galiba)
 * Dynamic demek unitydeki serializefield mantigi ile ayni sanirsim ha bi de Blueprint graphlari bunu gorebiliyormus = (Event Dispatcher)
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful); //dynamic yaparsak degisken turu virgul degisken ismi yapiyoruz, dynamic olmazsa fonksiyondaki gibi virgulle ayirmiyoruz
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful); //FOnlineSessionSearchResult Blueprint ile uyumlu degil, o yuzden Dynamic yapamiyoruz
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result); //EOnJoinSessionCompleteResult bu da usttekiyle ayni sebepten Dynamic degil
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);
/*Delege Deklarasyonlari Bitti*/
/**
 * 
 */
UCLASS()
class BERKUSHONLINE_API UBerkushOnlineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UBerkushOnlineSubsystem();

	//To Handle session functionality. The Menu class will call these
	void CreateSession(int32 NumPublicConnections, FString MatchType);
	void FindSessions(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SessionResult);
	void DestroySession();
	void StartSession();

	bool IsValidSessionInterface();

	//
	// Our own custom delegates for the Menu class to bind callbacks to
	//
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;
	FMultiplayerOnFindSessionsComplete MultiplayerOnFindSessionsComplete;
	FMultiplayerOnJoinSessionComplete MultiplayerOnJoinSessionComplete;
	FMultiplayerOnDestroySessionComplete MultiplayerOnDestroySessionComplete;
	FMultiplayerOnStartSessionComplete MultiplayerOnStartSessionComplete;

protected:

	//
	// Internal callbacks for the delegates we'll add to the Online Session Interface delegate list.
	// These don't need to be called outside this class.
	//
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

private:
	IOnlineSessionPtr SessionInterface;//=//TSharedPtr<UOnlineSession, ESPMode::ThreadSafe> ile ayni sey
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	//
	// To add to the Online Session Interface delegate list.
	// We'll bind our BerkushOnlineSubsystem internal callbacks to these.
	//
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	/*
	 *Eger Session olusturmamiz basarili olmazsa, Destroy Session ile onu Destroy edip, Fonksiyon girdileri ile tekrar cagirmak istiyoruz,
	 * bunu CreateSessionda yapamamizin nedeni, Destroy Sessionun da Asenkron fonksiyon olmasi, yani Create session icinde devam edecek suremiz bulunmuyor
	 */
	bool bCreateSessionOnDestroy{ false };
	int32 LastNumPublicConnections;
	FString LastMatchType;
};