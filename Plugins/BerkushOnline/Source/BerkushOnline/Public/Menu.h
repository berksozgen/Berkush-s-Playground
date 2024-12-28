// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void MenuSetup(int32 NumberOfPublicConnections = 8, FString TypeOfMatch = FString(TEXT("FreeForAll")));

protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* B_Host;
	UPROPERTY(meta = (BindWidget))
	class UButton* B_Join;

	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();

	//The Subsystem desigfned to handle all online session functionality
	class UBerkushOnlineSubsystem* OnlineSessionsSubsystem;

	int32 NumPublicConnections{8};
	FString MatchType{TEXT("FreeForAll")};
};
