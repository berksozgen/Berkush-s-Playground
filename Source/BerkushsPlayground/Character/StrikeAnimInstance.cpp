// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "StrikeAnimInstance.h"

#include "StrikeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	//Offset Yaw for Strafing
	FRotator AimRotaition = StrikeCharacter->GetBaseAimRotation(); //Bu global rotationu veriyor
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(StrikeCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotaition);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f); //Rotationlarda Lerp kullanmama sebebimiz -180 den 180 e giden yol lerpte -180 -> 0 ->180 iken burda yok
	YawOffset = DeltaRotation.Yaw;
	
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = StrikeCharacter->GetActorRotation(); //Bu rootun btw
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);
}
