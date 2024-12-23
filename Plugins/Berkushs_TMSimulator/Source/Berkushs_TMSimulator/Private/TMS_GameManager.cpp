// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "TMS_GameManager.h"

#include "SheepController.h"
#include "TMS_Player.h"

// Sets default values
ATMS_GameManager::ATMS_GameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMS_GameManager::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ATMS_Player>(GWorld->GetFirstPlayerController()->GetPawn());
	
	FVector PlayerLocation = Player->GetActorLocation();
	
	FActorSpawnParameters SheepSpawnInfo;
	SheepSpawnInfo.Owner = this;
	SheepSpawnInfo.Instigator = GetInstigator();
	SheepSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform SpawnTransform {};
	SpawnTransform.SetScale3D(FVector { 1.f, 1.f, 1.f });

	for(int i = 0; i < 35; i++)
	{
		FVector SpawnPos { FMath::RandRange(-2000.f, 2000.f) + PlayerLocation.X,
			FMath::RandRange(-2000.f, 2000.f) + PlayerLocation.Y, PlayerLocation.Z + 2000.f };
		SpawnTransform.SetLocation(SpawnPos);
		GWorld->SpawnActor(SheepClass, &SpawnTransform, SheepSpawnInfo);
	}

	SheepSpawnTimer(1.f);
	TimeLeftTimer(1.f);
}

// Called every frame
void ATMS_GameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATMS_GameManager::SheepSpawnTimer(float DelayTime)
{
	GetWorldTimerManager().SetTimer(
		SheepSpawnTimerHandle,
		this,
		&ATMS_GameManager::SheepSpawn,
		DelayTime,
		false
		);
}

void ATMS_GameManager::SheepSpawn()
{
	FVector PlayerLocation = Player->GetActorLocation();
	
	FActorSpawnParameters SheepSpawnInfo;
	SheepSpawnInfo.Owner = this;
	SheepSpawnInfo.Instigator = GetInstigator();
	SheepSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform SpawnTransform {};
	SpawnTransform.SetScale3D(FVector { 1.f, 1.f, 1.f });
	
	for (int i = 0; i < FMath::RandRange(1, 8); i++)
	{
		FVector SpawnPos { FMath::RandRange(-2000.f, 2000.f) + PlayerLocation.X,
	FMath::RandRange(-2000.f, 2000.f) + PlayerLocation.Y, PlayerLocation.Z + 2000.f };
		SpawnTransform.SetLocation(SpawnPos);
		GWorld->SpawnActor(SheepClass, &SpawnTransform, SheepSpawnInfo);
	}
	SheepSpawnTimer(FMath::RandRange(5.f, 15.f));
}

void ATMS_GameManager::TimeLeftTimer(float DelayTime)
{
	GetWorldTimerManager().SetTimer(
		SheepSpawnTimerHandle,
		this,
		&ATMS_GameManager::SheepSpawn,
		DelayTime,
		false
		);
}
	
void ATMS_GameManager::TimeLeftFun()
{
	TimeLeft--;
	if(TimeLeft>=1)	TimeLeftTimer(1.f);
	else GameOver();
}

	void ATMS_GameManager::GameOver()
{
	
}
