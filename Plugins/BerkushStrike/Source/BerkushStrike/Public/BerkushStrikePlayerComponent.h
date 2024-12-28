// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BerkushStrikePlayerComponent.generated.h"

UENUM(BlueprintType)
enum class EBerkushStrikeRoundResults : uint8
{
	Draw,
	Won,
	Lost,
};

UENUM(BlueprintType, Category = "BerkushStrike")
enum class EBerkushStrikePlayerTeam : uint8
{
	Red,
	Blue,
	Spectator,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BERKUSHSTRIKE_API UBerkushStrikePlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBerkushStrikePlayerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "BerkushStrike")
	void SetPlayerOverlay(class USkeletalMeshComponent* SkeletalMeshComponent, bool bIsRedTeam);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	EBerkushStrikePlayerTeam PlayerTeam = EBerkushStrikePlayerTeam::Spectator;

	class UMaterialInstance* RedTeamOverlayMaterial;
	class UMaterialInstance* BlueTeamOverlayMaterial;
};
