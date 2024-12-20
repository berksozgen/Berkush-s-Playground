// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BerkushsMultiplayerBase/MenuSystem/InGameMenu.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInGameMenu() {}

// Begin Cross Module References
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UInGameMenu();
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UInGameMenu_NoRegister();
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UMenuWidget();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UPackage* Z_Construct_UPackage__Script_BerkushsMultiplayerBase();
// End Cross Module References

// Begin Class UInGameMenu Function QuitPressed
struct Z_Construct_UFunction_UInGameMenu_QuitPressed_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MenuSystem/InGameMenu.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInGameMenu_QuitPressed_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UInGameMenu, nullptr, "QuitPressed", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInGameMenu_QuitPressed_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInGameMenu_QuitPressed_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UInGameMenu_QuitPressed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInGameMenu_QuitPressed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInGameMenu::execQuitPressed)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->QuitPressed();
	P_NATIVE_END;
}
// End Class UInGameMenu Function QuitPressed

// Begin Class UInGameMenu Function ReturnPressed
struct Z_Construct_UFunction_UInGameMenu_ReturnPressed_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MenuSystem/InGameMenu.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInGameMenu_ReturnPressed_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UInGameMenu, nullptr, "ReturnPressed", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInGameMenu_ReturnPressed_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInGameMenu_ReturnPressed_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UInGameMenu_ReturnPressed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInGameMenu_ReturnPressed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInGameMenu::execReturnPressed)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ReturnPressed();
	P_NATIVE_END;
}
// End Class UInGameMenu Function ReturnPressed

// Begin Class UInGameMenu
void UInGameMenu::StaticRegisterNativesUInGameMenu()
{
	UClass* Class = UInGameMenu::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "QuitPressed", &UInGameMenu::execQuitPressed },
		{ "ReturnPressed", &UInGameMenu::execReturnPressed },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UInGameMenu);
UClass* Z_Construct_UClass_UInGameMenu_NoRegister()
{
	return UInGameMenu::StaticClass();
}
struct Z_Construct_UClass_UInGameMenu_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "MenuSystem/InGameMenu.h" },
		{ "ModuleRelativePath", "MenuSystem/InGameMenu.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MenuSystem/InGameMenu.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_QuitButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MenuSystem/InGameMenu.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_QuitButton;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UInGameMenu_QuitPressed, "QuitPressed" }, // 2242542619
		{ &Z_Construct_UFunction_UInGameMenu_ReturnPressed, "ReturnPressed" }, // 38532183
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInGameMenu>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInGameMenu_Statics::NewProp_ReturnButton = { "ReturnButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInGameMenu, ReturnButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnButton_MetaData), NewProp_ReturnButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInGameMenu_Statics::NewProp_QuitButton = { "QuitButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInGameMenu, QuitButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_QuitButton_MetaData), NewProp_QuitButton_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInGameMenu_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInGameMenu_Statics::NewProp_ReturnButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInGameMenu_Statics::NewProp_QuitButton,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInGameMenu_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UInGameMenu_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UMenuWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_BerkushsMultiplayerBase,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInGameMenu_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInGameMenu_Statics::ClassParams = {
	&UInGameMenu::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UInGameMenu_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UInGameMenu_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInGameMenu_Statics::Class_MetaDataParams), Z_Construct_UClass_UInGameMenu_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UInGameMenu()
{
	if (!Z_Registration_Info_UClass_UInGameMenu.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInGameMenu.OuterSingleton, Z_Construct_UClass_UInGameMenu_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInGameMenu.OuterSingleton;
}
template<> BERKUSHSMULTIPLAYERBASE_API UClass* StaticClass<UInGameMenu>()
{
	return UInGameMenu::StaticClass();
}
UInGameMenu::UInGameMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UInGameMenu);
UInGameMenu::~UInGameMenu() {}
// End Class UInGameMenu

// Begin Registration
struct Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_InGameMenu_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInGameMenu, UInGameMenu::StaticClass, TEXT("UInGameMenu"), &Z_Registration_Info_UClass_UInGameMenu, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInGameMenu), 310991072U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_InGameMenu_h_1890637176(TEXT("/Script/BerkushsMultiplayerBase"),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_InGameMenu_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_InGameMenu_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
