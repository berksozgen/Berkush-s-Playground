// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BERKUSHSPLAYGROUND_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuffComponent();
	friend class AStrikeCharacter; //Tum degerlere (Protected ve Private ulasabiliyorz boyle)
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Heal(float HealAmount, float HealingTime);

protected:
	virtual void BeginPlay() override;
	
	void HealRampUp(float DeltaTime);

private:
	UPROPERTY()
	class AStrikeCharacter* Character;

	bool bHealing = false;
	float HealingRate = 0.f;
	float AmountToHeal = 0.f;

public:	
	
};