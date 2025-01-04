// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StrikeHUD.generated.h"

USTRUCT(BlueprintType)
struct FHudPackage
{
	GENERATED_USTRUCT_BODY()
public:
	class UTexture2D* CrosshairCenter;
	UTexture2D* CrosshairsLeft;
	UTexture2D* CrosshairsRight;
	UTexture2D* CrosshairsTop;
	UTexture2D* CrosshairsBottom;
	float CrosshairSpread;
	FLinearColor CrosshairsColor;
};

/**
 * 
 */
UCLASS()
class BERKUSHSPLAYGROUND_API AStrikeHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<class UUserWidget> CharacterOverlayClass;
	void AddCharacterOverlay();
	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;
protected:
	virtual void BeginPlay() override;

private:
	FHudPackage HUDPackage;

	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread); //adam coloru input param olarak ekledi, eklemem valla

	UPROPERTY(EditAnywhere)
	float CrosshairSpreadMax = 16.f;

public:
	FORCEINLINE void SetHUDPackage(const FHudPackage& Package) { HUDPackage = Package; }
	
};