// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "StrikeAnimInstance.h"

#include "StrikeCharacter.h"
#include "BerkushsPlayground/Weapon/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BerkushsPlayground/StrikeTypes/CombatState.h"

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
	EquippedWeapon = StrikeCharacter->GetEquippedWeapon();
	bIsCrouched = StrikeCharacter->bIsCrouched;
	bAiming = StrikeCharacter->IsAiming();
	TurningInPlace = StrikeCharacter->GetTurningInPlace();
	bRotateRootBone = StrikeCharacter->ShouldRotateRootBone();
	bElimmed = StrikeCharacter->IsElimmed();
	
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

	AO_Yaw = StrikeCharacter->GetAO_Yaw();
	AO_Pitch = StrikeCharacter->GetAO_Pitch();

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && StrikeCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		StrikeCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));

		if (StrikeCharacter->IsLocallyControlled()) /*Su silahin baktigi yonu, merminin gidecegi yone cevirmeyi sadece oynayanda yapacagiz, replike olmasina gerek yok (aslinda var da bandwith)*/
		{
			bLocallyControlled = true; //Bunu tickte setlemek ne kadar mantikli?
			FTransform RightHandTransform = StrikeCharacter->GetMesh()->GetSocketTransform(FName("Hand_R")/*btw bu kisim Case sensitive degilmis*/, ERelativeTransformSpace::RTS_World);
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(),
				RightHandTransform.GetLocation() + /*Ikinci kisma da elin lokasyonunu ekleyip cikarma nedenimiz skeletal meshde X eksini govdeye bakiyor, yoksa Get hit target yeterli*/
				(RightHandTransform.GetLocation() - StrikeCharacter->GetHitTarget()));

			RightHandRotation = FMath::RInterpTo(RightHandRotation, LookAtRotation, DeltaTime, 30.f);
		}
	}

	bUseFABRIK = StrikeCharacter->GetCombatState() != ECombatState::ECS_Reloading;
	bUseAimOffsets = StrikeCharacter->GetCombatState() != ECombatState::ECS_Reloading;
	bTransformRightHand = StrikeCharacter->GetCombatState() != ECombatState::ECS_Reloading;
}