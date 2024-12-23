// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "TMS_Bullet.h"
#include "UObject/ConstructorHelpers.h"




// Sets default values
ATMS_Bullet::ATMS_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> RedMaterial(TEXT("/Berkushs_TMSimulator/Resources/MI_TMS_Red"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> GreenMaterial(TEXT("/Berkushs_TMSimulator/Resources/MI_TMS_Green"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> BlueMaterial(TEXT("/Berkushs_TMSimulator/Resources/MI_TMS_Blue"));

	MI_RED = RedMaterial.Object;
	MI_GREEN = GreenMaterial.Object;
	MI_BLUE = BlueMaterial.Object;

}

// Called when the game starts or when spawned
void ATMS_Bullet::BeginPlay()
{
	Super::BeginPlay();

	switch (BulletColor)
	{
	case E_TMS_Color::Red:
		BulletMesh->SetMaterial(0, MI_RED);
		break;
	case E_TMS_Color::Green:
		BulletMesh->SetMaterial(0, MI_GREEN);
		break;
	case E_TMS_Color::Blue:
		BulletMesh->SetMaterial(0, MI_BLUE);
		break;
	default:
		break;
	}

	GetWorldTimerManager().SetTimer(
		DestroyHandler,
		this,
		&ATMS_Bullet::DestroyBullet,
		10.f,
		false
		);
}

void ATMS_Bullet::DestroyBullet()
{
	AActor::Destroy();
}

// Called every frame
void ATMS_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

