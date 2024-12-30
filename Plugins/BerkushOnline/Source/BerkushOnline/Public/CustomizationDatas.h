// 2024'te R. Berk Sozgen tarafindan gelistirilmeye baslanmistir.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "CustomizationDatas.generated.h"

USTRUCT(BlueprintType)
struct FPolygonFamilies : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMesh*> MaleSkeletalMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMesh*> FemaleSkeletalMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> AvailableTextures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> HairOrHats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> FaceWears;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> BeardOrMasks;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> Patches;
};

USTRUCT(BlueprintType)
struct FPolygonAttachmentData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StaticMeshIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) /*Textures Aren't Change Anything*/
	float HueShiftingAmount = 0.f;
};

USTRUCT(BlueprintType)
struct FPolygonCustomizationData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FamilyName = TEXT("Dummy");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsMale = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkeletalMeshIndex = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkeletalTextureIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkeletalHueShiftingAmount = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPolygonAttachmentData HairOrHatData= FPolygonAttachmentData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPolygonAttachmentData FaceWearData = FPolygonAttachmentData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPolygonAttachmentData BeardOrMaskData = FPolygonAttachmentData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPolygonAttachmentData PatchData = FPolygonAttachmentData();
};

/**
 * 
 */
UCLASS()
class BERKUSHONLINE_API UCustomizationDatas : public UObject
{
	GENERATED_BODY()
	
};
