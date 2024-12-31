// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "Menu.h"

#include "Components/Button.h"
#include "BerkushOnlineSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Components/WidgetSwitcher.h"
#include "Interfaces/OnlineSessionInterface.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch, FString LobbyPath)
{
	PathToLobby = FString::Printf(TEXT("%s?listen"), *LobbyPath);
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true); //bIsFocusable = true; //Deprached

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UBerkushOnlineSubsystem>();
	}

	//Bind Delegates
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions); // Bunlar Dynamic Olmadigi icin AddUObject diyoruz, mantik ayni Fonksiyona Bind Ediyor Kendini
		MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession); //Ustteki not bunun icin de gecerli
		MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		MultiplayerSessionsSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
	}
}

bool UMenu::Initialize()
{
	if(!Super::Initialize()) return false;

	if(SinglePlayerButton)
	{
		SinglePlayerButton->SetIsEnabled(false);
		//SinglePlayerButton->OnClicked.AddDynamic(this, &ThisClass::SinglePlayerButtonClicked);
	}
	if(HostSessionButton)
	{
		HostSessionButton->OnClicked.AddDynamic(this, &UMenu::HostSessionButtonClicked);
	}
	if(JoinSessionButton)
	{
		JoinSessionButton->OnClicked.AddDynamic(this, &ThisClass::JoinSessionButtonClicked);
	}
	if(CustomizeButton)
	{
		CustomizeButton->OnClicked.AddDynamic(this, &ThisClass::CustomizeButtonClicked);
	}
	if(SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &ThisClass::SettingsButtonClicked);
	}
	if(ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &ThisClass::ExitButtonClicked);
	}
	
	
	return true;
}

void UMenu::NativeDestruct()  //Level Hafizadan silinirken cagiriliyor, unrealin depreched yaptigi seylerden biri daha; normalde baska bir ismi vardi
{
	MenuTearDown();
	Super::NativeDestruct();
}

#pragma region DelegateCallbacks
void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(PathToLobby);
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Menu Callback: Failed to create session!"))
			);
		}
		HostSessionButton->SetIsEnabled(true);
	}
}

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful) //Su anda otomatik olarak ilk buldugu sessiona giriyor, MultiplayerBase ile birlestirmem lazim bunu
{
	if (MultiplayerSessionsSubsystem == nullptr)
	{
		return;
	}

	for (auto Result : SessionResults)
	{
		FString SettingsValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		if (SettingsValue == MatchType)
		{
			MultiplayerSessionsSubsystem->JoinSession(Result);
			return;
		}
	}
	if (!bWasSuccessful || SessionResults.Num() == 0)
	{
		JoinSessionButton->SetIsEnabled(true);
	}
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
	}
	if (Result != EOnJoinSessionCompleteResult::Success) //Haihazirda Session Bulundu, Ancak Host sessionu silmeden oyundan cikti, Connect string bozuk; bu check onun icin
	{
		JoinSessionButton->SetIsEnabled(true);
	}
}

void UMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMenu::OnStartSession(bool bWasSuccessful)
{
}
#pragma endregion DelegateCallbacks

#pragma region ButtonFunctions
void UMenu::HostSessionButtonClicked()
{
	SecondaryMenuSwitcher->SetActiveWidget(BlankMenu); //Still Progress
	HostSessionButton->SetIsEnabled(false);
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void UMenu::JoinSessionButtonClicked()
{
	SecondaryMenuSwitcher->SetActiveWidget(BlankMenu); //Still Progress
	JoinSessionButton->SetIsEnabled(false);
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->FindSessions(10'000); //Steam DevAppId 480 icin 10'000 vermek iyi,, Kendi Buildimde 100'e ya da 1000'e alcam
	}
}

void UMenu::CustomizeButtonClicked()
{
	SecondaryMenuSwitcher->SetActiveWidget(CustomizeMenu);
	CustomizeButton->SetIsEnabled(false);
	SettingsButton->SetIsEnabled(true);
}

void UMenu::SettingsButtonClicked()
{
	SecondaryMenuSwitcher->SetActiveWidget(SettingsMenu);
	SettingsButton->SetIsEnabled(false);
	CustomizeButton->SetIsEnabled(true);
}

void UMenu::ExitButtonClicked()
{
	UWorld* World = GetWorld();
	if (!ensure(World!=nullptr)) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}
#pragma endregion ButtonFunctions

void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}

void UMenu::SetPrimaryButtonsRGB(float DeltaTime, float CycleTime)
{
	//Red artacak, 1 olunca green artacak, green 1 olunca red azakup blue artacak, blue 1 olunce green azalip red artacak //Umarim negatif sayilar hata verdirtmiyordur
	if(RedColorTime>=1.f)
	{
		BlueColorTime -= DeltaTime/CycleTime;
		GreenColorTime += DeltaTime/CycleTime;
	}
	if (GreenColorTime>=1.f)
	{
		RedColorTime -= DeltaTime/CycleTime;
		BlueColorTime += DeltaTime/CycleTime;
	}
	if (BlueColorTime>=1.f)
	{
		GreenColorTime -= DeltaTime/CycleTime;
		RedColorTime += DeltaTime/CycleTime;
	}
	FLinearColor OutputColor = FLinearColor(RedColorTime, GreenColorTime, BlueColorTime);
	SinglePlayerButton->SetBackgroundColor(OutputColor);
	HostSessionButton->SetBackgroundColor(OutputColor);
	JoinSessionButton->SetBackgroundColor(OutputColor);
	CustomizeButton->SetBackgroundColor(OutputColor);
	SettingsButton->SetBackgroundColor(OutputColor);
	ExitButton->SetBackgroundColor(OutputColor);
}
