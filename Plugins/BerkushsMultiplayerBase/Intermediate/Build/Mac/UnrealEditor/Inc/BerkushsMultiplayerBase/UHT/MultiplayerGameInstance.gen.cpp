// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BerkushsMultiplayerBase/Public/MultiplayerGameInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMultiplayerGameInstance() {}

// Begin Cross Module References
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UMenuInterface_NoRegister();
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UMultiplayerGameInstance();
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UMultiplayerGameInstance_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
UPackage* Z_Construct_UPackage__Script_BerkushsMultiplayerBase();
// End Cross Module References

// Begin Class UMultiplayerGameInstance Function Host
struct Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics
{
	struct MultiplayerGameInstance_eventHost_Parms
	{
		FString ServerName;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MultiplayerGameInstance.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::NewProp_ServerName = { "ServerName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MultiplayerGameInstance_eventHost_Parms, ServerName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::NewProp_ServerName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMultiplayerGameInstance, nullptr, "Host", nullptr, nullptr, Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::MultiplayerGameInstance_eventHost_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020601, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::MultiplayerGameInstance_eventHost_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMultiplayerGameInstance_Host()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMultiplayerGameInstance_Host_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMultiplayerGameInstance::execHost)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_ServerName);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Host(Z_Param_ServerName);
	P_NATIVE_END;
}
// End Class UMultiplayerGameInstance Function Host

// Begin Class UMultiplayerGameInstance Function InGameLoadMenu
struct Z_Construct_UFunction_UMultiplayerGameInstance_InGameLoadMenu_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Menu" },
		{ "ModuleRelativePath", "Public/MultiplayerGameInstance.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMultiplayerGameInstance_InGameLoadMenu_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMultiplayerGameInstance, nullptr, "InGameLoadMenu", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMultiplayerGameInstance_InGameLoadMenu_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMultiplayerGameInstance_InGameLoadMenu_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UMultiplayerGameInstance_InGameLoadMenu()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMultiplayerGameInstance_InGameLoadMenu_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMultiplayerGameInstance::execInGameLoadMenu)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InGameLoadMenu();
	P_NATIVE_END;
}
// End Class UMultiplayerGameInstance Function InGameLoadMenu

// Begin Class UMultiplayerGameInstance Function Join
struct Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics
{
	struct MultiplayerGameInstance_eventJoin_Parms
	{
		uint32 Index;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MultiplayerGameInstance.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_Index;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FUInt32PropertyParams Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MultiplayerGameInstance_eventJoin_Parms, Index), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::NewProp_Index,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMultiplayerGameInstance, nullptr, "Join", nullptr, nullptr, Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::MultiplayerGameInstance_eventJoin_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020601, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::MultiplayerGameInstance_eventJoin_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UMultiplayerGameInstance_Join()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMultiplayerGameInstance_Join_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMultiplayerGameInstance::execJoin)
{
	P_GET_PROPERTY(FUInt32Property,Z_Param_Index);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Join(Z_Param_Index);
	P_NATIVE_END;
}
// End Class UMultiplayerGameInstance Function Join

// Begin Class UMultiplayerGameInstance Function LoadMenuWidget
struct Z_Construct_UFunction_UMultiplayerGameInstance_LoadMenuWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Menu" },
		{ "ModuleRelativePath", "Public/MultiplayerGameInstance.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMultiplayerGameInstance_LoadMenuWidget_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMultiplayerGameInstance, nullptr, "LoadMenuWidget", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMultiplayerGameInstance_LoadMenuWidget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMultiplayerGameInstance_LoadMenuWidget_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UMultiplayerGameInstance_LoadMenuWidget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMultiplayerGameInstance_LoadMenuWidget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMultiplayerGameInstance::execLoadMenuWidget)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->LoadMenuWidget();
	P_NATIVE_END;
}
// End Class UMultiplayerGameInstance Function LoadMenuWidget

// Begin Class UMultiplayerGameInstance
void UMultiplayerGameInstance::StaticRegisterNativesUMultiplayerGameInstance()
{
	UClass* Class = UMultiplayerGameInstance::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Host", &UMultiplayerGameInstance::execHost },
		{ "InGameLoadMenu", &UMultiplayerGameInstance::execInGameLoadMenu },
		{ "Join", &UMultiplayerGameInstance::execJoin },
		{ "LoadMenuWidget", &UMultiplayerGameInstance::execLoadMenuWidget },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMultiplayerGameInstance);
UClass* Z_Construct_UClass_UMultiplayerGameInstance_NoRegister()
{
	return UMultiplayerGameInstance::StaticClass();
}
struct Z_Construct_UClass_UMultiplayerGameInstance_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "MultiplayerGameInstance.h" },
		{ "ModuleRelativePath", "Public/MultiplayerGameInstance.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMultiplayerGameInstance_Host, "Host" }, // 1653289934
		{ &Z_Construct_UFunction_UMultiplayerGameInstance_InGameLoadMenu, "InGameLoadMenu" }, // 1912243761
		{ &Z_Construct_UFunction_UMultiplayerGameInstance_Join, "Join" }, // 3909336241
		{ &Z_Construct_UFunction_UMultiplayerGameInstance_LoadMenuWidget, "LoadMenuWidget" }, // 4194049453
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMultiplayerGameInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UMultiplayerGameInstance_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstance,
	(UObject* (*)())Z_Construct_UPackage__Script_BerkushsMultiplayerBase,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMultiplayerGameInstance_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_UMultiplayerGameInstance_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UMenuInterface_NoRegister, (int32)VTABLE_OFFSET(UMultiplayerGameInstance, IMenuInterface), false },  // 3346524662
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMultiplayerGameInstance_Statics::ClassParams = {
	&UMultiplayerGameInstance::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	UE_ARRAY_COUNT(InterfaceParams),
	0x009000A8u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMultiplayerGameInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UMultiplayerGameInstance_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMultiplayerGameInstance()
{
	if (!Z_Registration_Info_UClass_UMultiplayerGameInstance.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMultiplayerGameInstance.OuterSingleton, Z_Construct_UClass_UMultiplayerGameInstance_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMultiplayerGameInstance.OuterSingleton;
}
template<> BERKUSHSMULTIPLAYERBASE_API UClass* StaticClass<UMultiplayerGameInstance>()
{
	return UMultiplayerGameInstance::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMultiplayerGameInstance);
UMultiplayerGameInstance::~UMultiplayerGameInstance() {}
// End Class UMultiplayerGameInstance

// Begin Registration
struct Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMultiplayerGameInstance, UMultiplayerGameInstance::StaticClass, TEXT("UMultiplayerGameInstance"), &Z_Registration_Info_UClass_UMultiplayerGameInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMultiplayerGameInstance), 251687390U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_3562430391(TEXT("/Script/BerkushsMultiplayerBase"),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
