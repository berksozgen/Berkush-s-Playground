// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "BerkushsMultiplayerBase/MenuSystem/MenuInterface.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MultiplayerGameInstance.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FSPlayerCustomizationFamilies : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMesh*> MaleSkeletalMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMesh*> FemaleSkeletalMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> AvailableTextures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> HairOrHats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> FaceWears;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> BeardOrMasks;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> Patches;
};

USTRUCT(BlueprintType)
struct FSPlayerAttachmentData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StaticMeshIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) /*Textures Arent Change Anything*/
	float HueShiftingAmount = 0.f;
};

USTRUCT(BlueprintType)
struct FSPlayerCustomizationData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FamilyName = TEXT("BattleRoyale");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsMale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkeletalMeshIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkeletalTextureIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkeletalHueShiftingAmount = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSPlayerAttachmentData HairOrHatData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSPlayerAttachmentData FaceWearData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSPlayerAttachmentData BeardOrMaskData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSPlayerAttachmentData PatchData;
	
};

UCLASS()
class BERKUSHSMULTIPLAYERBASE_API UMultiplayerGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UMultiplayerGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void InGameLoadMenu();
	
	UFUNCTION(Exec)
	void Host(FString ServerName) override;
	
	UFUNCTION(Exec)
	void Join(uint32 Index) override;

	void StartSession();

	virtual void LoadMainMenu() override;

	void RefreshServerList() override;

	UPROPERTY(EditAnywhere, Category = "Berkush's Multiplayer Base")
	FString MainMenuPath = TEXT("/Game/Maps/MainMenu");

	UPROPERTY(EditAnywhere, Category = "Berkush's Multiplayer Base")
	FString LobbyPath = TEXT("/Game/Maps/Lobby/Lobby");

	UFUNCTION(BlueprintCallable, Category = "Berkush's Multiplayer Base")
	FSPlayerCustomizationData GetPlayerCustomizationData() { return PlayerCustomizationData; }
	UFUNCTION(BlueprintCallable, Category = "Berkush's Multiplayer Base")
	void SetPlayerCustomizationData(FSPlayerCustomizationData _PlayerCustomizationData) { PlayerCustomizationData = _PlayerCustomizationData; }
	
private:
	TSubclassOf<class UUserWidget> MenuClass; //class yazmak forward decklarition oluyor galiba, include u burada yapmadik diye belirttik, normalde gerek yok
	TSubclassOf<class UUserWidget> InGameMenuClass;
	
	class UMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);	
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

	FString DesiredServerName;
	void CreateSession();

	FSPlayerCustomizationData PlayerCustomizationData;
	
};
