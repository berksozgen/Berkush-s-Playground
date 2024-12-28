// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
//
#include "Interfaces/OnlineSessionInterface.h"

//
#include "BerkushOnlineSubsystem.generated.h"

//
//Declaring our own custom delegates for the Menu class to bind callbacks to
//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnlineOnCreateSessionComplete, bool, bWasSuccesful);

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

	//
	//Our own custom delegetes for the Menu class to bind callcaks to
	//

protected:

	//Internal callbacks for the delegates we will add to OnlineSessionInterface delegate list.
	//This don't need to be called outside this class.
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

private:
	IOnlineSessionPtr SessionInterface; //=//TSharedPtr<UOnlineSession, ESPMode::ThreadSafe> ile ayni sey
	TSharedPtr<FOnlineSessionSettings> LastCreatedSessionSettings;

	//To add to the Online Session Interface delegate list.
	//Also, we will bind BerkushOnlineSubsytem internal callbacks to these.
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
	//
	
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
