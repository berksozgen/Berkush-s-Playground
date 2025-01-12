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
#include "BerkushsPlayground/StrikeComponents/CombatComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; //Eger bu false olsaydi, weapon sinifimiz gene her makinede calisacakti ama her clientin uzerinde hasauthoritysi olacakti, biz mermi mekanigi sadece serverde calissin istiyoruz o yuzden replike ediyoruz bunu
	SetReplicateMovement(true); //Bunu acma nedenizim eleman falan havada olurse dustugu yer ile serverdeke yer birbiriyle uysun diye
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	//WeaponMesh->SetupAttachment(RootComponent);
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
	WeaponMesh->MarkRenderStateDirty(); //Renderer'in bunu tekrar renderlamasiini sagliyor kabaca
	EnableCustomDepth(true);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);
}

void AWeapon::EnableCustomDepth(bool bEnable)
{
	if (WeaponMesh)
	{
		WeaponMesh->SetRenderCustomDepth(bEnable);
	}
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
	OnWeaponStateSet();
}

void AWeapon::OnRep_WeaponState()
{
	OnWeaponStateSet();
}

void AWeapon::OnWeaponStateSet()
{
	switch (WeaponState)
	{
	case EWeaponState::EWS_Equipped:
		HandleEquipped();
		break;
	case EWeaponState::EWS_EquippedSecondary:
		HandleEquippedSecondary();
		break;
	case EWeaponState::EWS_Dropped:
		HandleDropped();
		break;
	}
}

void AWeapon::HandleEquipped()
{
	ShowPickupWidget(false);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision); //bunu aslinda sadece serverde yapiytoruz ama clientte de cagirmamizin zarari yok
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetEnableGravity(false);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (WeaponType == EWeaponType::EWT_SubMachineGun) //Sadece smgde kayis var diye 
	{
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}
	EnableCustomDepth(false);
}

void AWeapon::HandleEquippedSecondary()
{
	ShowPickupWidget(false);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetEnableGravity(false);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (WeaponType == EWeaponType::EWT_SubMachineGun)
	{
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}
	EnableCustomDepth(true);
	if (WeaponMesh)
	{
		WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_TAN);
		WeaponMesh->MarkRenderStateDirty();
	}
}

void AWeapon::HandleDropped()
{
	//ShowPickupWidget(true); //adam bunu eklemedi de ben eklim bari// galba gerek yok buna
	if (HasAuthority())	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true); //aslinda normalde enable geliyor ama anlasilir kod olsu diye actik tekrar
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Bu da SMG ayarlari bozuyor diye, bir kayis icin ugrastigim seye bak
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	//
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
	WeaponMesh->MarkRenderStateDirty();
	EnableCustomDepth(true);
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
	StrikeOwnerCharacter = StrikeOwnerCharacter == nullptr ? Cast<AStrikeCharacter>(GetOwner()) : StrikeOwnerCharacter; //Bunu sonradan eklemis galina adam
	if (StrikeOwnerCharacter && StrikeOwnerCharacter->GetCombat() && IsFull())
	{
		StrikeOwnerCharacter->GetCombat()->JumpToShotgunEnd();
	}
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
		StrikeOwnerCharacter = StrikeOwnerCharacter == nullptr ? Cast<AStrikeCharacter>(Owner) : StrikeOwnerCharacter;
		if (StrikeOwnerCharacter && StrikeOwnerCharacter->GetEquippedWeapon() && StrikeOwnerCharacter->GetEquippedWeapon() == this) //su 2. bloga gerek var mi, nulla thisi karsilastircak mantiken zaten
		{
			SetHUDAmmo();
		}
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

bool AWeapon::IsFull()
{
	return Ammo == MagCapacity;
}
