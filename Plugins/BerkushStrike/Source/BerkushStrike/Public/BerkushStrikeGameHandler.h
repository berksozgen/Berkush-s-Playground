// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BerkushStrikeGameHandler.generated.h"

UCLASS()
class BERKUSHSTRIKE_API ABerkushStrikeGameHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABerkushStrikeGameHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	UFUNCTION(BlueprintCallable, Category = "BerkushStrike")
	FTransform GiveSpawnLocation(class UBerkushStrikePlayerComponent* BerkushStrikeComponent);
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	class UBoxComponent* RedTeamSpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	class UBoxComponent* BlueTeamSpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BerkushStrike")
	TArray<AActor*> SpawnObjects;
	
	TSubclassOf<class APawn> PlayerPawnClass;

private:
	UClass* PlayerClass;

};
