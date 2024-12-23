// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "TMS_Player.h"
#include "TMS_Bullet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATMS_Player::ATMS_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	HeadLevel = CreateDefaultSubobject<USceneComponent>(TEXT("HeadLevel"));
	HeadLevel->SetupAttachment(CapsuleComponent);
	
	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(HeadLevel); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GunHole = CreateDefaultSubobject<USceneComponent>(TEXT("GunHole"));
	GunHole->SetupAttachment(CapsuleComponent);

	SetNextBulletColor();
}

// Called when the game starts or when spawned
void ATMS_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATMS_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATMS_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATMS_Player::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ATMS_Player::Shoot);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATMS_Player::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATMS_Player::Look);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TMS Karakterinde EnhancedInputComponent patladi"));
	}
}

void ATMS_Player::Shoot()
{
	if (bCanFire)
	{
		bCanFire = false;
		
		FTransform GunHoleTransform = GunHole->GetComponentTransform();
	
		FActorSpawnParameters BulletSpawnInfo;
		BulletSpawnInfo.Owner = this;
		BulletSpawnInfo.Instigator = GetInstigator();
		BulletSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ATMS_Bullet* Bullet = Cast<ATMS_Bullet>( GWorld->SpawnActor(BulletClass, &GunHoleTransform, BulletSpawnInfo));
		Bullet->BulletColor = BulletColor;
		SetNextBulletColor();
		BulletsFired++;
		
		GetWorldTimerManager().SetTimer(
			FireHandle,
			this,
			&ATMS_Player::ResetCanFire,
		(BulletsFired%5) ? 1.f : 3.f,
		false
		);
	}
}

void ATMS_Player::Jump()
{
	AddMovementInput(FVector::UpVector, 500.f, true);
}

void ATMS_Player::SetNextBulletColor()
{
	int32 Random = FMath::RandRange(0,2);
	BulletColor = (Random == 0) ? E_TMS_Color::Red : (Random == 1) ? E_TMS_Color::Green : E_TMS_Color::Blue;
}

void ATMS_Player::ResetCanFire()
{
	bCanFire = true;
}

void ATMS_Player::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATMS_Player::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
