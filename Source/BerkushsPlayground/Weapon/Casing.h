// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casing.generated.h"

UCLASS()
class BERKUSHSPLAYGROUND_API ACasing : public AActor
{
	GENERATED_BODY()
	
public:	
	ACasing();

protected:
	virtual void BeginPlay() override;

	UFUNCTION() //Callback fonksiyonu oldugu icin UFUNCTION makrosu zorunlu, Unreal boyle calisiyo
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CasingMesh;
	
	UPROPERTY(EditAnywhere)
	float ShellEjectionImpulse;
	
	UPROPERTY(EditAnywhere)
	class USoundCue* ShellSound;
};
