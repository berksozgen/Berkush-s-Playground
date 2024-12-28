// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "Menu.h"

#include "Components/Button.h"
#include "BerkushOnlineSubsystem.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch)
{
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsEnabled(true); //bIsFocusable = true; //Deprached

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
		OnlineSessionsSubsystem = GameInstance->GetSubsystem<UBerkushOnlineSubsystem>();
	}
}

bool UMenu::Initialize()
{
	if(!Super::Initialize()) return false;

	if(B_Host)
	{
		B_Host->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
	}
	if(B_Join)
	{
		B_Join->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
	
	return true;
}

void UMenu::NativeConstruct()
{
	MenuTearDown();
	Super::NativeConstruct();
}

#pragma region Buttons

void UMenu::HostButtonClicked()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Purple,
			FString::Printf(TEXT("HostButtonClicked")));
	}

	if(OnlineSessionsSubsystem)
	{
		OnlineSessionsSubsystem->CreateSession(NumPublicConnections, MatchType);
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/Maps/Lobby/Lobby?listen");
		}
	}
}

void UMenu::JoinButtonClicked()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Purple,
			FString::Printf(TEXT("JoinButtonClicked")));
	}
}

#pragma endregion Buttons

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
