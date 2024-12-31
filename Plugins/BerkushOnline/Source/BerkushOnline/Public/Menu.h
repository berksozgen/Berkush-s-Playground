// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHONLINE_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Berkush Online|Menu")
	void MenuSetup(int32 NumberOfPublicConnections = 8, FString TypeOfMatch = FString(TEXT("FreeForAll")), FString LobbyPath = FString(TEXT("/Game/Maps/Lobby/Lobby")));

	UFUNCTION(BlueprintCallable, Category = "Berkush Online|Menu")
	void SetPrimaryButtonsRGB(float DeltaTime, float CycleTime);

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	//
	// Callback for the custom delegates on BerkushOnlineSubsystem
	// Bunlarin Ufunction Olmasi Gerekiyormus
	//
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
private:
#pragma region PrimaryMenuElements
	UPROPERTY(meta = (BindWidget))
	class UButton* SinglePlayerButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* HostSessionButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinSessionButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* CustomizeButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* SettingsButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;
#pragma endregion PrimaryMenuElements
#pragma region SecondaryMenuElements
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* SecondaryMenuSwitcher;
	UPROPERTY(meta = (BindWidget))
	class UWidget* BlankMenu;
	UPROPERTY(meta = (BindWidget))
	class UWidget* SinglePlayerMenu;
	UPROPERTY(meta = (BindWidget))
	class UWidget* HostSessionMenu;
	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinSessionMenu;
	UPROPERTY(meta = (BindWidget))
	class UWidget* CustomizeMenu;
	UPROPERTY(meta = (BindWidget))
	class UWidget* SettingsMenu;
#pragma endregion SecondaryMenuElements

#pragma region PrimaryMenuFunctions
	UFUNCTION()
	void HostSessionButtonClicked();
	UFUNCTION()
	void JoinSessionButtonClicked();
	UFUNCTION()
	void CustomizeButtonClicked();
	UFUNCTION()
	void SettingsButtonClicked();
	UFUNCTION()
	void ExitButtonClicked();
#pragma endregion PrimaryMenuFunctions

	void MenuTearDown();

	// The subsystem designed to handle all online session functionality
	class UBerkushOnlineSubsystem* MultiplayerSessionsSubsystem;

	int32 NumPublicConnections{4};
	FString MatchType{TEXT("FreeForAll")};
	FString PathToLobby{TEXT("")};
	
	float RedColorTime = 1.f;
	float GreenColorTime = 0.f;
	float BlueColorTime = 0.f;
};
