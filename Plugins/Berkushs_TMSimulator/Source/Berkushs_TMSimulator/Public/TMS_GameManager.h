// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TMS_GameManager.generated.h"


UCLASS()
class BERKUSHS_TMSIMULATOR_API ATMS_GameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMS_GameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "TMSimulator_Alpha")
	int32 KillCount {0};
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "TMSimulator_Alpha")
    int32 TimeLeft {90};
    TSubclassOf<class ASheepController> SheepClass;

    class ATMS_Player* Player;

	FTimerHandle SheepSpawnTimerHandle;
	void SheepSpawnTimer(float DelayTime);
	void SheepSpawn();

	FTimerHandle TimeLeftHandle;
	void TimeLeftTimer(float DelayTime);
	void TimeLeftFun();

	void GameOver();
};