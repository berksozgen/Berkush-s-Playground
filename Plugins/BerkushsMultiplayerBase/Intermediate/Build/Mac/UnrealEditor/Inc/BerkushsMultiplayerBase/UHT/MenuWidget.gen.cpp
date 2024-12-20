// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BerkushsMultiplayerBase/MenuSystem/MenuWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMenuWidget() {}

// Begin Cross Module References
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UMenuWidget();
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UMenuWidget_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_BerkushsMultiplayerBase();
// End Cross Module References

// Begin Class UMenuWidget
void UMenuWidget::StaticRegisterNativesUMenuWidget()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMenuWidget);
UClass* Z_Construct_UClass_UMenuWidget_NoRegister()
{
	return UMenuWidget::StaticClass();
}
struct Z_Construct_UClass_UMenuWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "MenuSystem/MenuWidget.h" },
		{ "ModuleRelativePath", "MenuSystem/MenuWidget.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMenuWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UMenuWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_BerkushsMultiplayerBase,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMenuWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMenuWidget_Statics::ClassParams = {
	&UMenuWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMenuWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UMenuWidget_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMenuWidget()
{
	if (!Z_Registration_Info_UClass_UMenuWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMenuWidget.OuterSingleton, Z_Construct_UClass_UMenuWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMenuWidget.OuterSingleton;
}
template<> BERKUSHSMULTIPLAYERBASE_API UClass* StaticClass<UMenuWidget>()
{
	return UMenuWidget::StaticClass();
}
UMenuWidget::UMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMenuWidget);
UMenuWidget::~UMenuWidget() {}
// End Class UMenuWidget

// Begin Registration
struct Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_MenuWidget_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMenuWidget, UMenuWidget::StaticClass, TEXT("UMenuWidget"), &Z_Registration_Info_UClass_UMenuWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMenuWidget), 3973784469U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_MenuWidget_h_1010356723(TEXT("/Script/BerkushsMultiplayerBase"),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_MenuWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_MenuWidget_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
