// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.


#include "Weapon.h"

#include "Casing.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "BerkushsPlayground/Character/StrikeCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Animation/AnimationAsset.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BerkushsPlayground/PlayerController/StrikePlayerController.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; //Eger bu false olsaydi, weapon sinifimiz gene her makinede calisacakti ama her clientin uzerinde hasauthoritysi olacakti, biz mermi mekanigi sadece serverde calissin istiyoruz o yuzden replike ediyoruz bunu

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	//WeaponMesh->SetupAttachment(RootComponent);
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority()/*GetLocalRole()==ENetRole::ROLE_Authority*/)
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
		AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnSphereEndOverlap);
	}
	
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(false);
	}
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region NetworkEvents
void AWeapon::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, WeaponState);
	DOREPLIFETIME(AWeapon, Ammo);
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(OtherActor);
	if (StrikeCharacter)
	{
		StrikeCharacter->SetOverlappingWeapon(this);
	}
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AStrikeCharacter* StrikeCharacter = Cast<AStrikeCharacter>(OtherActor);
	if (StrikeCharacter)
	{
		StrikeCharacter->SetOverlappingWeapon(nullptr);
	}
}

void AWeapon::SetWeaponState(EWeaponState State)
{
	WeaponState = State;
	
	switch (WeaponState)
	{
	case EWeaponState::EWS_Equipped:
		ShowPickupWidget(false);
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponMesh->SetSimulatePhysics(false);
		WeaponMesh->SetEnableGravity(false);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	case EWeaponState::EWS_Dropped:
		if (HasAuthority())	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		WeaponMesh->SetSimulatePhysics(true);
		WeaponMesh->SetEnableGravity(true); //aslinda normalde enable geliyor ama anlasilir kod olsu diye actik tekrar
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	}
}

void AWeapon::OnRep_WeaponState()
{
	switch (WeaponState)
	{
	case EWeaponState::EWS_Equipped:
		ShowPickupWidget(false);
		WeaponMesh->SetSimulatePhysics(false);
		WeaponMesh->SetEnableGravity(false);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	case EWeaponState::EWS_Dropped:
		//ShowPickupWidget(true); //adam bunu eklemedi de ben eklim bari// galba gerek yok buna
		WeaponMesh->SetSimulatePhysics(true);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	}
}

void AWeapon::ShowPickupWidget(bool bShowWidget)
{
	if(PickupWidget)
	{
		PickupWidget->SetVisibility(bShowWidget);
	}
}
#pragma endregion NetworkEvents

void AWeapon::Fire(const FVector& HitTarget) //Networke alabilirim bunu
{
	if (FireAnimation)
	{
		WeaponMesh->PlayAnimation(FireAnimation, false);
	}
	if (CasingClass)
	{
		const USkeletalMeshSocket* AmmoEjectSocket = WeaponMesh->GetSocketByName(FName("AmmoEject"));
		if (AmmoEjectSocket)
		{
			FTransform SocketTransform = AmmoEjectSocket->GetSocketTransform(WeaponMesh);
			
			UWorld* World = GetWorld();
			if (World)
			{
				World->SpawnActor<ACasing>(
					CasingClass,
					SocketTransform.GetLocation(),
					SocketTransform.GetRotation().Rotator());
			}
		}
	}
	SpendRound();
}

void AWeapon::SetHUDAmmo()
{
	StrikeOwnerCharacter = StrikeOwnerCharacter == nullptr ? Cast<AStrikeCharacter>(GetOwner()) : StrikeOwnerCharacter;
	if (StrikeOwnerCharacter)
	{
		StrikeOwnerController = StrikeOwnerController == nullptr ? Cast<AStrikePlayerController>(StrikeOwnerCharacter->Controller) : StrikeOwnerController;
		if (StrikeOwnerController)
		{
			StrikeOwnerController->SetHUDWeaponAmmo(Ammo);
		}
	}
}

void AWeapon::SpendRound() //Server Only
{
	Ammo = FMath::Clamp(Ammo - 1, 0, MagCapacity);
	SetHUDAmmo();
}

void AWeapon::OnRep_Ammo() //Clients only
{
	SetHUDAmmo();
}

void AWeapon::OnRep_Owner() //Bu da client only, Server silahi aldigi gibi bu fonksiyonu cagirmasi icin; CombatComponentten ayarliyoz onu
{
	Super::OnRep_Owner();
	if (Owner == nullptr)
	{
		StrikeOwnerCharacter = nullptr;
		StrikeOwnerController = nullptr;
	}
	else
	{
		SetHUDAmmo();
	}
}

void AWeapon::Dropped()
{
	SetWeaponState(EWeaponState::EWS_Dropped);
	FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld,true/*Bu kismi anlamadim*/);
	WeaponMesh->DetachFromComponent(DetachRules);
	SetOwner(nullptr);
	StrikeOwnerCharacter = nullptr;
	StrikeOwnerController = nullptr;
}

void AWeapon::AddAmmo(int32 AmmoToAdd)
{
	Ammo = FMath::Clamp(Ammo - AmmoToAdd, 0, MagCapacity); //Bu da negatif yollama essekligini yapariz diye, cok ta gerek yok gerci
	SetHUDAmmo(); //Serverda da calissin diye
}

bool AWeapon::IsEmpty()
{
	return Ammo <= 0;
}
