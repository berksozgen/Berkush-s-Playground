// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#include "Door.h"

#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	//SetReplicateMovement(true); //merge change

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	DoorMesh->SetupAttachment(RootComponent);
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	FrontCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("FrontCollision"));
	FrontCollision->SetupAttachment(DoorMesh);
	FrontCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	FrontCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BackCollision"));
	BackCollision->SetupAttachment(DoorMesh);
	BackCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DoorWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DoorWidget"));
	DoorWidget->SetupAttachment(DoorMesh);
}

void ADoor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADoor, DoorState);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		FrontCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		FrontCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		FrontCollision->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnFrontCollisionOverlap);
		FrontCollision->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnCollisionBoxesEndOverlap);

		BackCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BackCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		BackCollision->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnBackCollisionOverlap);
		BackCollision->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnCollisionBoxesEndOverlap);
	}
	
	if (DoorWidget)
	{
		DoorWidget->SetVisibility(false);
	}
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*

	if (HasAuthority() && bIsCurrentlyMoving)
	{
		const float NewRotation = MovementDirection * DeltaTime / MovingTime;
		DoorMesh->SetRelativeRotation(FRotator(0.f, 0.f, NewRotation));
		if (FMath::Abs(NewRotation) >= FMath::Abs(MovementDirection) || (MovementDirection <= KINDA_SMALL_NUMBER && FMath::Abs(NewRotation) <= KINDA_SMALL_NUMBER)) //IOkincisi sifir olma durumu
		{
			bIsCurrentlyMoving = false;
			DoorState = FMath::Abs(NewRotation) <= KINDA_SMALL_NUMBER ? EDoorState::EDS_Closed : NewRotation >= 90.f ? EDoorState::EDS_OpenedFront : EDoorState::EDS_OpenedBack;
			OnRep_DoorState(); //custom func yazamam valla
		}
	}
	*/

}

void ADoor::OnFrontCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(OtherActor);
	if (StrikeCharacter) StrikeCharacter->SetOverlappingDoor(this);
	//Set Player On front
	if (DoorState == EDoorState::EDS_Closed) NextDoorState = EDoorState::EDS_OpenedFront;
	else if (DoorState == EDoorState::EDS_OpenedBack) NextDoorState = EDoorState::EDS_Closed;
}

void ADoor::OnBackCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(OtherActor);
	if (StrikeCharacter) StrikeCharacter->SetOverlappingDoor(this);
	//Set Player On Back
	if (DoorState == EDoorState::EDS_Closed) NextDoorState = EDoorState::EDS_OpenedBack;
	else if (DoorState == EDoorState::EDS_OpenedFront) NextDoorState = EDoorState::EDS_Closed;
}

void ADoor::OnCollisionBoxesEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(OtherActor);
	if (StrikeCharacter) StrikeCharacter->SetOverlappingDoor(nullptr);
}
// Relative Rotation Z = 90 == Open Front
// 0 == Closed
// -90 == Open Back 
void ADoor::InteractWithDoor()
{
	DoorState = NextDoorState;
	Multicast_Temp_UpdateDoorState(DoorState);

	/*
	if (!bIsCurrentlyMoving)
	{
		bIsCurrentlyMoving = true;
		switch (NextDoorState)
		{
		case EDoorState::EDS_Closed:
			MovementDirection = 0.f;
			break;
		case EDoorState::EDS_OpenedFront:
			MovementDirection = 90.f;
			break;
		case EDoorState::EDS_OpenedBack:
			MovementDirection = -90.f;
			break;
		}
	}
	*/
}

void ADoor::Multicast_Temp_UpdateDoorState_Implementation(EDoorState State)
{
	switch (State)
	{
	case EDoorState::EDS_Closed:
		DoorMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		break;
	case EDoorState::EDS_OpenedFront:
		DoorMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
		break;
	case EDoorState::EDS_OpenedBack:
		DoorMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		break;
	}
}

void ADoor::OnRep_DoorState() //clientlerde olmuyor niyeyse multicast atayim da akillansin unreal
{
	/*
	//bIsCurrentlyMoving = true;
	switch (NextDoorState)
	{
	case EDoorState::EDS_Closed:
		DoorMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		break;
	case EDoorState::EDS_OpenedFront:
		DoorMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
		break;
	case EDoorState::EDS_OpenedBack:
		DoorMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		break;
	}
	*/
}


void ADoor::ShowDoorWidget(bool bShow)
{
	if (DoorWidget) DoorWidget->SetVisibility(bShow);
}
