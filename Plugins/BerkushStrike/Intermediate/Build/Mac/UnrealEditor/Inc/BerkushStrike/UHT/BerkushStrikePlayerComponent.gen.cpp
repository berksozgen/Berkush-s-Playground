// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BerkushStrike/Public/BerkushStrikePlayerComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBerkushStrikePlayerComponent() {}

// Begin Cross Module References
BERKUSHSTRIKE_API UClass* Z_Construct_UClass_UBerkushStrikePlayerComponent();
BERKUSHSTRIKE_API UClass* Z_Construct_UClass_UBerkushStrikePlayerComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
UPackage* Z_Construct_UPackage__Script_BerkushStrike();
// End Cross Module References

// Begin Class UBerkushStrikePlayerComponent
void UBerkushStrikePlayerComponent::StaticRegisterNativesUBerkushStrikePlayerComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBerkushStrikePlayerComponent);
UClass* Z_Construct_UClass_UBerkushStrikePlayerComponent_NoRegister()
{
	return UBerkushStrikePlayerComponent::StaticClass();
}
struct Z_Construct_UClass_UBerkushStrikePlayerComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "BerkushStrikePlayerComponent.h" },
		{ "ModuleRelativePath", "Public/BerkushStrikePlayerComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBerkushStrikePlayerComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UBerkushStrikePlayerComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_BerkushStrike,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBerkushStrikePlayerComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBerkushStrikePlayerComponent_Statics::ClassParams = {
	&UBerkushStrikePlayerComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBerkushStrikePlayerComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UBerkushStrikePlayerComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBerkushStrikePlayerComponent()
{
	if (!Z_Registration_Info_UClass_UBerkushStrikePlayerComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBerkushStrikePlayerComponent.OuterSingleton, Z_Construct_UClass_UBerkushStrikePlayerComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBerkushStrikePlayerComponent.OuterSingleton;
}
template<> BERKUSHSTRIKE_API UClass* StaticClass<UBerkushStrikePlayerComponent>()
{
	return UBerkushStrikePlayerComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBerkushStrikePlayerComponent);
UBerkushStrikePlayerComponent::~UBerkushStrikePlayerComponent() {}
// End Class UBerkushStrikePlayerComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushStrike_Source_BerkushStrike_Public_BerkushStrikePlayerComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBerkushStrikePlayerComponent, UBerkushStrikePlayerComponent::StaticClass, TEXT("UBerkushStrikePlayerComponent"), &Z_Registration_Info_UClass_UBerkushStrikePlayerComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBerkushStrikePlayerComponent), 1341025912U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushStrike_Source_BerkushStrike_Public_BerkushStrikePlayerComponent_h_4141305678(TEXT("/Script/BerkushStrike"),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushStrike_Source_BerkushStrike_Public_BerkushStrikePlayerComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushStrike_Source_BerkushStrike_Public_BerkushStrikePlayerComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
