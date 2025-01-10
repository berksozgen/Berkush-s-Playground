// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UENUM(BlueprintType)
enum class EDoorState : uint8
{
	EDS_Closed UMETA(DisplayName = "Closed"),
	EDS_OpenedFront UMETA(DisplayName = "Opened Front"),
	EDS_OpenedBack UMETA(DisplayName = "Opened Back"),

	EDS_MAX UMETA(DisplayName = "DefaultMAX") //Unreal istiyormus bunu galiba
};

UCLASS()
class BERKUSHSPLAYGROUND_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoor();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Tick(float DeltaTime) override;

	void InteractWithDoor(); //bunu da sadece server cagiracak

	void ShowDoorWidget(bool bShow);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnFrontCollisionOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnBackCollisionOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnCollisionBoxesEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere, Category = "Door Properties")
	class UStaticMeshComponent* DoorMesh;
	
	UPROPERTY(EditAnywhere, Category = "Door Properties")
	class UBoxComponent* FrontCollision;

	UPROPERTY(EditAnywhere, Category = "Door Properties")
	class UBoxComponent* BackCollision;

	UPROPERTY(VisibleAnywhere, Category = "Door Properties")
	class UWidgetComponent* DoorWidget;

	UPROPERTY(ReplicatedUsing = OnRep_DoorState, VisibleAnywhere, Category = "Door Properties")
	EDoorState DoorState;

	UFUNCTION(NetMulticast, Reliable) //Rep Notifylar bozuk ugrasamam valla
	void Multicast_Temp_UpdateDoorState(EDoorState State);

	UPROPERTY(EditAnywhere, Category = "Door Properties")
	float MovingTime = .5f;

	EDoorState NextDoorState; //Server ONLY State, It determines which side will be open

	UFUNCTION()
	void OnRep_DoorState();

	bool bIsCurrentlyMoving = false;
	float MovementDirection = 0.f;

public:	
};
