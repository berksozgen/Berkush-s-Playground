#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_AssaultRifle UMETA(DisplayName = "Assault Rifle"),
	EWT_Pistol UMETA(DisplayName = "Pistol"),
	EWT_SniperRifle UMETA(DisplayName = "Sniper Rifle"),

	EWT_MAX UMETA(DisplayName = "DefaultMAX") //Unreal istiyormus bunu galiba
};