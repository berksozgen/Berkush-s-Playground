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
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	virtual float GetServerTime(); //Synced with server world clock
	virtual void ReceivedPlayer() override; // Sync with server clock as soon as possible
protected:
	virtual void BeginPlay() override;
	void SetHUDTime();

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
private:
	UPROPERTY()
	class AStrikeHUD* StrikeHUD;

	float MatchTime = 120.f;
	uint32 CountdownInt = 0;
};