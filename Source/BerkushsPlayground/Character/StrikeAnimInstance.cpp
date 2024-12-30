// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "StrikeAnimInstance.h"

#include "StrikeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UStrikeAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	StrikeCharacter = Cast<AStrikeCharacter>(TryGetPawnOwner());
}

void UStrikeAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (StrikeCharacter == nullptr)
	{
		StrikeCharacter = Cast<AStrikeCharacter>(TryGetPawnOwner());
	}
	if (StrikeCharacter == nullptr) return; //Redundant Flow Control Jump this state diyor rider, compile ederken jumplarsa naneyi yerim, ya da ustteki bloga entegre ederse

	FVector Velocity = StrikeCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = StrikeCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = StrikeCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f; //Burda da ternary kullandi, goz alisikligi yapmak icin herhal
	bWeaponEquipped = StrikeCharacter->IsWeaponEquipped();
	bIsCrouched = StrikeCharacter->bIsCrouched;
	bAiming = StrikeCharacter->IsAiming();
}
