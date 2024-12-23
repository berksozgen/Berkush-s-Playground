// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SheepController.h"
#include "TMS_Bullet.generated.h"

UCLASS()
class BERKUSHS_TMSIMULATOR_API ATMS_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMS_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DestroyBullet();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	E_TMS_Color BulletColor;

	UStaticMeshComponent* BulletMesh;
	UMaterialInstance* MI_RED;
	UMaterialInstance* MI_GREEN;
	UMaterialInstance* MI_BLUE;

	FTimerHandle DestroyHandler;
};
