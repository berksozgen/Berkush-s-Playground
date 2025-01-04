// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StrikePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API AStrikePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDKills(int32 Kills);
	void SetHUDDeaths(int32 Deaths);
	void SetHUDKilledText(FString KilledText);
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDWeaponAmmoType(FString AmmoType);
	void SetHUDMatchCountdown(float CountdownTime);
	void SetHUDAnnouncementCountdown(float CountdownTime);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual float GetServerTime(); //Synced with server world clock
	virtual void ReceivedPlayer() override; // Sync with server clock as soon as possible
	void OnMatchStateSet(FName State);
protected:
	virtual void BeginPlay() override;
	void SetHUDTime();
	void PollInit();

	//Sync time between client and server
	//Request the current server time, passing in the client's time when the request was sent (btw direkt getworldtime seconds ile tutsak ya lokal bir degiskende, servere niye yolluyoz)
	UFUNCTION(Server, Reliable)
	void Server_RequestServerTime(float TimeOfClientRequest);
	//Reports the current server time to the client in response to Server_RequestServerTime
	UFUNCTION(Client, Reliable)
	void Client_ReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	float ClientServerDelta = 0.f; //Difference between client and server time
	UPROPERTY(EditAnywhere, Category = Time)
	float TimeSyncFrequency = 5.f;
	float TimeSyncRunningTime = 0.f;
	void CheckTimeSync(float DeltaTime);
	void HandleMatchHasStarted();
	void HandleCooldown();

	UFUNCTION(Server, Reliable)
	void Server_CheckMatchState();

	UFUNCTION(Client, Reliable)
	void Client_JoinMidGame(FName _StateOfMatch, float _StartingTime, float _WarmupTime, float _MatchTime, float _CooldownTime);
private:
	UPROPERTY()
	class AStrikeHUD* StrikeHUD;

	UPROPERTY() //for server
	class AStrikeGameMode* StrikeGameMode;

	float LevelStartingTime = 0.f;
	float MatchTime = 0.f;
	float WarmupTime = 0.f;
	float CooldownTime = 0.f;
	uint32 CountdownInt = 0;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;
	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY() //Aslinda sethud da da cagirabiliriz bunu, simdiki kodda canlar yenilenmedigi icin cagiriyoruz
	class UCharacterOverlay* CharacterOverlay;
	bool bInitializeCharacterOverlay = false;
	float HUDHealth;
	float HUDMaxHealth;
	float HUDScore;
	int32 HUDKills;
	int32 HUDDeaths;
};