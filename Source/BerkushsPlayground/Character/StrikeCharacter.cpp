// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "StrikeCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BerkushsPlayground/StrikeComponents/CombatComponent.h"
#include "BerkushsPlayground/Weapon/Weapon.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

AStrikeCharacter::AStrikeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);

	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	Combat->SetIsReplicated(true);

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	//Fix camera, birileri araya gecince zoom yapmasin diye
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void AStrikeCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AStrikeCharacter, OverlappingWeapon, COND_OwnerOnly);

	//DOREPLIFETIME(AStrikeCharacter, OverlappingWeapon); //Boyle yapinca biri silah ustunde durunca herkeste gozulkuyor
}

void AStrikeCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(Combat)
	{
		Combat->Character = this;
	}
}

void AStrikeCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AStrikeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region Input
void AStrikeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(StrikeMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStrikeCharacter::EnhancedMove);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStrikeCharacter::EnhancedLook);

		// Equipping
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &AStrikeCharacter::EquipPressed);
		
		// Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AStrikeCharacter::CrouchPressed);
		
		// Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AStrikeCharacter::AimPressed);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AStrikeCharacter::AimReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Strike Karakteri EnhancedInputComponent'i Aktive Edemedi"));
	}
}

void AStrikeCharacter::EnhancedMove(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	MoveForward(MovementVector.Y);
	MoveRight(MovementVector.X);
}

void AStrikeCharacter::EnhancedLook(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	Turn(LookAxisVector.X);
	LookUp(LookAxisVector.Y);
}

void AStrikeCharacter::EquipPressed(const FInputActionValue& Value) //Parametrelere gerek var mi bilmiyorum, Enhanced input mal ama biraz
{
	if (Combat)
	{
		if (HasAuthority())
		{
			Combat->EquipWeapon(OverlappingWeapon);
		}
		else
		{
			Server_EquipButtonPressed();
		}
	}
}

void AStrikeCharacter::CrouchPressed(const FInputActionValue& Value)
{
	if (bIsCrouched) UnCrouch();
	else Crouch();
}

void AStrikeCharacter::AimPressed(const FInputActionValue& Value)
{
	if (Combat)
	{
		Combat->SetAiming(true);
	}
}

void AStrikeCharacter::AimReleased(const FInputActionValue& Value)
{
	if (Combat)
	{
		Combat->SetAiming(false);
	}
}

void AStrikeCharacter::MoveForward(float Value)
{
	if(Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void AStrikeCharacter::MoveRight(float Value)
{
	if(Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void AStrikeCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AStrikeCharacter::LookUp(float Value)
{
	AddControllerPitchInput(-Value);
}
#pragma endregion Input

#pragma region Replication
void AStrikeCharacter::Server_EquipButtonPressed_Implementation()
{
	if (Combat)
	{
		Combat->EquipWeapon(OverlappingWeapon);
	}
}

void AStrikeCharacter::SetOverlappingWeapon(AWeapon* Weapon) //Bu kod, Weapon'un Collision Handle'lamasi yuzunden sadece serverde calisiyor
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(false); //Bu kisim da sadece serverde calisiyor, yani degeri degistirmeden once silah varsa kapiyor
	}
	OverlappingWeapon = Weapon;
	if (IsLocallyControlled()) //Yani bu if check niye gerekli bilemedim //Bunu acikliyor galiba ama anlamadim 46. ders sonu
	{
		if (OverlappingWeapon)
		{
			OverlappingWeapon->ShowPickupWidget(true);
		}
	}
}

void AStrikeCharacter::OnRep_OverlappingWeapon(AWeapon* LastWeapon) //RepNotify'lar asla serverde calismaz! //Rep notify ile giren girdi degerleri, replikasyon olmadan onceki degeri dondurur, biraz kafa karistirici
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(true);
	}
	if (LastWeapon)
	{
		LastWeapon->ShowPickupWidget(false);
	}
}

bool AStrikeCharacter::IsWeaponEquipped() //Yari replication ile ilgili sayilir bu aslinda, tum Clientlerde AnimInstance guncellemeleri ile ilgili
{
	return Combat && Combat->EquippedWeapon;
}

bool AStrikeCharacter::IsAiming() //Yari replication ile ilgili sayilir bu aslinda, tum Clientlerde AnimInstance guncellemeleri ile ilgili
{
	return Combat && Combat->bAiming;
}
#pragma endregion Replication
