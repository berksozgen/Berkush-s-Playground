// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SheepController.generated.h"

UENUM(BlueprintType, Category = "TMSimulator_Alpha")
enum class E_TMS_Color : uint8
{
    Red,
    Green,
    Blue
};

UCLASS()
class BERKUSHS_TMSIMULATOR_API ASheepController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASheepController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    UStaticMeshComponent* SheepMesh;
	UMaterialInstance* MI_RED;
	UMaterialInstance* MI_GREEN;
	UMaterialInstance* MI_BLUE;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "TMSimulator_Alpha")
    TArray<UParticleSystem*> Effects;
	class ATMS_GameManager* GameManager;

    FVector RandomForce;

    E_TMS_Color Color;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    //ctor da GameManger atamasini yap

private:
    FTimerHandle SheepTimerHandle;
    void RandomMoveTimer(float DelayTime);
    void RandomMove();
};