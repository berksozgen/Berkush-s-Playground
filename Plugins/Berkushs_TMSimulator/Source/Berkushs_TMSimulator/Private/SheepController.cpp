// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "SheepController.h"
#include "TMS_Bullet.h"
#include "TMS_GameManager.h"



// Sets default values
ASheepController::ASheepController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> RedMaterial(TEXT("/Berkushs_TMSimulator/Resources/MI_TMS_Red"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> GreenMaterial(TEXT("/Berkushs_TMSimulator/Resources/MI_TMS_Green"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> BlueMaterial(TEXT("/Berkushs_TMSimulator/Resources/MI_TMS_Blue"));
	MI_RED = RedMaterial.Object;
	MI_GREEN = GreenMaterial.Object;
	MI_BLUE = BlueMaterial.Object;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sheep(TEXT("/Berkushs_TMSimulator/Resources/TMS_Sheep"));

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SheepMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SheepMesh"));
	SheepMesh->SetupAttachment(RootComponent);
	SheepMesh->SetStaticMesh(Sheep.Object);

	SheepMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ASheepController::BeginPlay()
{
	Super::BeginPlay();

	int32 SheepColor = FMath::RandRange(0,2);
	
	switch (SheepColor)
	{
	case 0:
		SheepMesh->SetMaterial(0, MI_RED);
		Color = E_TMS_Color::Red;
		break;
	case 1:
		SheepMesh->SetMaterial(0, MI_GREEN);
		Color = E_TMS_Color::Green;
		break;
	case 2:
		SheepMesh->SetMaterial(0, MI_BLUE);
		Color = E_TMS_Color::Blue;
		break;
	default:
		break;
	}
	//gameObject.GetComponent<Renderer>().material.color = new Color32((byte)Random.Range(0, 256), (byte)Random.Range(0, 256), (byte)Random.Range(0, 256), 255);
	//renderMaterial.color = Color.black;

	UE_LOG(LogTemp, Warning, TEXT("Koyun Begin Play Before Timer"));
	
	float DelayTime = FMath::RandRange(2.f,10.f);
	RandomMoveTimer(DelayTime);
	
	UE_LOG(LogTemp, Warning, TEXT("Koyun Begin Play After Timer"));
}

// Called every frame
void ASheepController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASheepController::RandomMoveTimer(float DelayTime)
{
	UE_LOG(LogTemp, Warning, TEXT("RandomMoveTimeActivated = %f"),DelayTime);
	GetWorldTimerManager().SetTimer(
		SheepTimerHandle,
		this,
		&ASheepController::RandomMove,
		DelayTime,
		false
		);
}

void ASheepController::RandomMove()
{
	float UNREAL_WANTS_FUVKING_MORE_THAN_UNITY = 5'000.f;
	float _ShortVer = UNREAL_WANTS_FUVKING_MORE_THAN_UNITY;
	SheepMesh->AddImpulse(FVector { FMath::RandRange(-50.f * _ShortVer, 50.f * _ShortVer), FMath::RandRange(-50.f * _ShortVer, 50.f * _ShortVer), FMath::RandRange(0.f, 20.f * _ShortVer)} );
	UE_LOG(LogTemp, Warning, TEXT("RandomMove"));
	RandomMoveTimer(FMath::RandRange(2.f, 10.f));
}

void ASheepController::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ATMS_Bullet* Bullet = Cast<ATMS_Bullet>(OtherActor);

	if(Bullet==nullptr) return;

	if(Bullet->BulletColor == Color) GameManager->KillCount++;
	else GameManager->KillCount--;

	Bullet->Destroy();
	//Spawn particle
	//pos ayarlar
	Destroy();
}

/* Activate the fuze to explode the bomb after several seconds */
/*
void ASBombActor::OnUsed(APawn* InstigatorPawn)
{
	GetWorld()->GetTimerManager().SetTimer(
	  FuzeTimerHandle, // handle to cancel timer at a later time
	  this, // the owning object
	  &ASBombActor::OnExplode, // function to call on elapsed
	  MaxFuzeTime, // float delay until elapsed
	  false); // looping?
}
*/
