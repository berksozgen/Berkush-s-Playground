// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GoKartMovingComponent.h"

#include "GoKartMovementReplicator.generated.h"

USTRUCT()
struct FGoKartState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FTransform Transform = FTransform();
	
	UPROPERTY()
	FVector Velocity = FVector::Zero();
	
	UPROPERTY()
	FGoKartMove LastMove = FGoKartMove();
};

struct FHermiteCubicSpline
{
	FVector StartLocation, StartDerivative, TargetLocation, TargetDerivative;

	FVector InterpolateLocation(float LerpRatio) const
	{
		return FMath::CubicInterp(StartLocation, StartDerivative, TargetLocation, TargetDerivative, LerpRatio);
	}
	FVector InterpolateDerivative(float LerpRatio) const
	{
		return FMath::CubicInterpDerivative(StartLocation, StartDerivative, TargetLocation, TargetDerivative, LerpRatio);
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST_KRAYZKARTS_API UGoKartMovementReplicator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementReplicator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMeshOffsetRoot(USceneComponent* Root) {MeshOffsetRoot = Root;}

private:
	
	void ClearAcknowledgeMoves(FGoKartMove LastMove);

	void UpdateServerState(const FGoKartMove& Move);

	void ClientTick(float DeltaTime);
	FHermiteCubicSpline CreateSpline();
	void InterpolateLocation(const FHermiteCubicSpline& Spline, float LerpRatio);
	void InterpolateVelocity(const FHermiteCubicSpline& Spline, float LerpRatio);
	void InterpolateRotation(float LerpRatio);
	float VelocityToDerivative();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SendMove(FGoKartMove Move);

	UPROPERTY(ReplicatedUsing=OnRep_ServerState)
	FGoKartState ServerState;

	UFUNCTION()
	void OnRep_ServerState();
	void AutonomousProxy_OnRep_ServerState();
	void SimulatedProxy_OnRep_ServerState();

	TArray<FGoKartMove> UnacknowledgedMoves;

	float ClientTimeSinceUpdate = 0;
	float ClientTimeBetweenLastUpdates;
	FTransform ClientStartTransform;
	FVector ClientStartVelocity;

	float ClientSimulatedTime;

	UPROPERTY()
	UGoKartMovingComponent* MovingComponent;

	bool bIsOwnerLocallyControlled = false;

	UPROPERTY()
	USceneComponent* MeshOffsetRoot;
};