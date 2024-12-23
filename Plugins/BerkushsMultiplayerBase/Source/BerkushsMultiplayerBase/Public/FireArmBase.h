// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Runtime/Engine/Classes/Engine/DataTable.h"

#include "FireArmBase.generated.h"

UENUM(BlueprintType, Category = "BerkushsMultiplayerBase")
enum class EFireArmSlot : uint8
{
	Primary,
	Secondary,
};

UENUM(BlueprintType, Category = "BerkushsMultiplayerBase")
enum class EFireArmType : uint8
{
	Pistol,
	SMG,
	Shotgun,
	Riffle,
	SniperRiffle,
	AutoSniperRiffle,
	MachineGun,
};

UENUM(BlueprintType, Category = "BerkushsMultiplayerBase")
enum class EAttachmentType : uint8
{
	Scope,
	Magazine,
	FlashLight,
	LazerLight,
};

UENUM(BlueprintType, Category = "BerkushsMultiplayerBase")
enum class EBulletType : uint8
{
	_9MM,
	_45ACP,
	_556,
	_762,
	_Magnum,
};

USTRUCT(BlueprintType, Category = "Berkush's Multiplayer Base")
struct FSFireArmInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	FText DisplayName = FText::FromString(TEXT("NULL WEAPON"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	FText WeaponDescription = FText::FromString(TEXT("NULL DESCRIPTION"));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	USkeletalMesh* WeaponMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	USkeletalMesh* MagazineMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	UParticleSystem* FireEffect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	UParticleSystem* HitEffect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	UParticleSystem* BloodEffect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	USoundCue* FireSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	USoundCue* HitSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	USoundCue* ReloadSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	EFireArmSlot WeaponSlot = EFireArmSlot::Primary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	EFireArmType WeaponType = EFireArmType::Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	bool bIsAutomatic = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	float ShootingWaitTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	float ReloadingWaitTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	float Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	float Accuracy = 0.f; //Smaller value is better

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	int32 Price = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	TArray<EAttachmentType> AvailableAttachments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	int32 MagazineSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	EBulletType BulletType = EBulletType::_9MM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Berkush's Multiplayer Base")
	int32 PickupBulletCount = 0;
};

UCLASS()
class BERKUSHSMULTIPLAYERBASE_API AFireArmBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireArmBase();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Berkush's Multiplayer Base")
	USkeletalMeshComponent* GunSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Berkush's Multiplayer Base")
	USkeletalMeshComponent* MagazineSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Berkush's Multiplayer Base")
	FSFireArmInfo WeaponInfo;

	UPROPERTY(BlueprintReadOnly, Category = "Berkush's Multiplayer Base")
	int32 MagazineAmmo;
	
	UFUNCTION(BlueprintCallable, Category="Berkush's Multiplayer Base")
	virtual void StartShooting();

	UFUNCTION(BlueprintCallable, Category="Berkush's Multiplayer Base")
	virtual void StopShooting();

	void ShootingHandler();

	bool bIsCurrentlyShooting { false };

	UFUNCTION(Server, Reliable, WithValidation, Category = "Berkush's Multiplayer Base")
	void Server_Shooting();

	UFUNCTION(NetMulticast, Unreliable, Category="Berkush's Multiplayer Base")
	void Multicast_Shooting(const FHitResult& Hit);

private:
	FTimerHandle FShootingHandler;
	
};
