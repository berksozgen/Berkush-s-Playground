// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TEST_KrayzKarts/Public/GoKart.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGoKart() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_APawn();
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
TEST_KRAYZKARTS_API UClass* Z_Construct_UClass_AGoKart();
TEST_KRAYZKARTS_API UClass* Z_Construct_UClass_AGoKart_NoRegister();
TEST_KRAYZKARTS_API UClass* Z_Construct_UClass_UGoKartMovementReplicator_NoRegister();
TEST_KRAYZKARTS_API UClass* Z_Construct_UClass_UGoKartMovingComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_TEST_KrayzKarts();
// End Cross Module References

// Begin Class AGoKart
void AGoKart::StaticRegisterNativesAGoKart()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AGoKart);
UClass* Z_Construct_UClass_AGoKart_NoRegister()
{
	return AGoKart::StaticClass();
}
struct Z_Construct_UClass_AGoKart_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "GoKart.h" },
		{ "ModuleRelativePath", "Public/GoKart.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** MappingContext */" },
#endif
		{ "ModuleRelativePath", "Public/GoKart.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "MappingContext" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "Public/GoKart.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovingComponent_MetaData[] = {
		{ "Category", "GoKart" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GoKart.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovementReplicator_MetaData[] = {
		{ "Category", "GoKart" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GoKart.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoxComponent_MetaData[] = {
		{ "Category", "GoKart" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GoKart.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshOffsetRootComponent_MetaData[] = {
		{ "Category", "GoKart" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GoKart.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMeshComponent_MetaData[] = {
		{ "Category", "GoKart" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GoKart.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MovingComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MovementReplicator;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BoxComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MeshOffsetRootComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkeletalMeshComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGoKart>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoKart_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoKart, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContext_MetaData), NewProp_DefaultMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoKart_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoKart, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoKart_Statics::NewProp_MovingComponent = { "MovingComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoKart, MovingComponent), Z_Construct_UClass_UGoKartMovingComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovingComponent_MetaData), NewProp_MovingComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoKart_Statics::NewProp_MovementReplicator = { "MovementReplicator", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoKart, MovementReplicator), Z_Construct_UClass_UGoKartMovementReplicator_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovementReplicator_MetaData), NewProp_MovementReplicator_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoKart_Statics::NewProp_BoxComponent = { "BoxComponent", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoKart, BoxComponent), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoxComponent_MetaData), NewProp_BoxComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoKart_Statics::NewProp_MeshOffsetRootComponent = { "MeshOffsetRootComponent", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoKart, MeshOffsetRootComponent), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshOffsetRootComponent_MetaData), NewProp_MeshOffsetRootComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGoKart_Statics::NewProp_SkeletalMeshComponent = { "SkeletalMeshComponent", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGoKart, SkeletalMeshComponent), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMeshComponent_MetaData), NewProp_SkeletalMeshComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGoKart_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoKart_Statics::NewProp_DefaultMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoKart_Statics::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoKart_Statics::NewProp_MovingComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoKart_Statics::NewProp_MovementReplicator,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoKart_Statics::NewProp_BoxComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoKart_Statics::NewProp_MeshOffsetRootComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGoKart_Statics::NewProp_SkeletalMeshComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGoKart_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AGoKart_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APawn,
	(UObject* (*)())Z_Construct_UPackage__Script_TEST_KrayzKarts,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGoKart_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AGoKart_Statics::ClassParams = {
	&AGoKart::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AGoKart_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AGoKart_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGoKart_Statics::Class_MetaDataParams), Z_Construct_UClass_AGoKart_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AGoKart()
{
	if (!Z_Registration_Info_UClass_AGoKart.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGoKart.OuterSingleton, Z_Construct_UClass_AGoKart_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AGoKart.OuterSingleton;
}
template<> TEST_KRAYZKARTS_API UClass* StaticClass<AGoKart>()
{
	return AGoKart::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AGoKart);
AGoKart::~AGoKart() {}
// End Class AGoKart

// Begin Registration
struct Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKart_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AGoKart, AGoKart::StaticClass, TEXT("AGoKart"), &Z_Registration_Info_UClass_AGoKart, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGoKart), 1067340047U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKart_h_362714495(TEXT("/Script/TEST_KrayzKarts"),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKart_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKart_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
