// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "BerkushOnlineSubsystem.h"
//
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

UBerkushOnlineSubsystem::UBerkushOnlineSubsystem() :
	CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)), //ThisClass = UBerkushOnlineSubsystem, Unreal Macrosu Gibi Birsey
	FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete)),
	JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
	DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
	StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
		
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Blue,
				FString::Printf(TEXT("Found Substem %s"), *Subsystem->GetSubsystemName().ToString()));
		}
	}
}

#pragma region CreateSession

void UBerkushOnlineSubsystem::CreateSession(int32 NumPublicConnections, FString MatchType)
{
	if(!SessionInterface.IsValid()) return;

	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		SessionInterface->DestroySession(NAME_GameSession);
	}

	//Store the delegate in a FDelegateHandle so we can later remove it from the delegate list
	CreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	LastCreatedSessionSettings = MakeShareable(new FOnlineSessionSettings());
	LastCreatedSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	LastCreatedSessionSettings->NumPublicConnections = NumPublicConnections;
	LastCreatedSessionSettings->bAllowJoinInProgress = true;
	LastCreatedSessionSettings->bAllowJoinViaPresence = true;
	LastCreatedSessionSettings->bShouldAdvertise = true;
	LastCreatedSessionSettings->bUsesPresence = true;
	LastCreatedSessionSettings->bUseLobbiesIfAvailable = true;
	LastCreatedSessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing); //Odalari sifreleyebiliriz bununla

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastCreatedSessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}
}

void UBerkushOnlineSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Green,
				FString::Printf(TEXT("Created session: %s"), *SessionName.ToString()));
		}

		UWorld* World = GetWorld();
		if(World)
		{
			World->ServerTravel(FString("/Game/Maps/Lobby/Lobby?listen")); //Fstringe gerek var mi bilmiyorum
		}
	
	}
	else
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString::Printf(TEXT("Failed to create session!")));
		}
	}
}

#pragma endregion CreateSession
#pragma region FindSessions

void UBerkushOnlineSubsystem::FindSessions(int32 MaxSearchResults)
{
		/*
	if(!OnlineSessionInterface.IsValid()) return;

	OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);
	
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 100; //Adam 10'000 verdi bana gerek yok bir sure
	SessionSearch->bIsLanQuery = false;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
	*/
}

void UBerkushOnlineSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
		/*
	if(!OnlineSessionInterface.IsValid()) return;
	
	for (auto Result : SessionSearch->SearchResults)
	{
		FString Id = Result.GetSessionIdStr();
		FString User = Result.Session.OwningUserName;
		FString MatchType;
		Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Magenta,
				FString::Printf(TEXT("Id: %s, User: %s"),*Id,*User));
		}
		if (MatchType == FString("FreeForAll"))
		{
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString::Printf(TEXT("Joining Match Type: %s"),*MatchType));
			}

			OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
		}
	}
	*/
}

#pragma endregion FindSessions
#pragma region StartSession

void UBerkushOnlineSubsystem::StartSession()
{
		
		
}

void UBerkushOnlineSubsystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
		
}

#pragma endregion StartSession
#pragma region DestroySession

void UBerkushOnlineSubsystem::DestroySession()
{
	
}

void UBerkushOnlineSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
		
}

#pragma endregion DestroySession
#pragma region JoinSession

void UBerkushOnlineSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
		
}

void UBerkushOnlineSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
		/*
	if(!OnlineSessionInterface.IsValid()) return;
	
	FString Address;
	if(OnlineSessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString::Printf(TEXT("Connect string: %s"),*Address));
		}

		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if(PlayerController)
		{
			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
	}
	*/
}

#pragma endregion JoinSession