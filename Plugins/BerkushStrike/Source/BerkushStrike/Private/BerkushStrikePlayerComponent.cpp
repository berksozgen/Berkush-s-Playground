// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "BerkushStrikePlayerComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UBerkushStrikePlayerComponent::UBerkushStrikePlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> BlueTeamOverlay(TEXT("/BerkushStrike/Materials/MI_BlueTeam_Overlay"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> RedTeamOverlay(TEXT("/BerkushStrike/Materials/MI_RedTeam_Overlay"));
	RedTeamOverlayMaterial = RedTeamOverlay.Object;
	BlueTeamOverlayMaterial = BlueTeamOverlay.Object;
}


// Called when the game starts
void UBerkushStrikePlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBerkushStrikePlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBerkushStrikePlayerComponent::SetPlayerOverlay(class USkeletalMeshComponent* SkeletalMeshComponent, bool bIsRedTeam)
{
	SkeletalMeshComponent->SetOverlayMaterial(bIsRedTeam ? RedTeamOverlayMaterial : BlueTeamOverlayMaterial);
	//Also dont forget the add overlay distance
}

