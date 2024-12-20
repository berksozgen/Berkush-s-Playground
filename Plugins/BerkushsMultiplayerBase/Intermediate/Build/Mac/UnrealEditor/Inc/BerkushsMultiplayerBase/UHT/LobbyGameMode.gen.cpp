// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BerkushsMultiplayerBase/Public/LobbyGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLobbyGameMode() {}

// Begin Cross Module References
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_ALobbyGameMode();
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_ALobbyGameMode_NoRegister();
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_AMultiplayerGameMode();
UPackage* Z_Construct_UPackage__Script_BerkushsMultiplayerBase();
// End Cross Module References

// Begin Class ALobbyGameMode Function StartGame
struct Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics
{
	struct LobbyGameMode_eventStartGame_Parms
	{
		FString MapPath;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LobbyGameMode.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_MapPath;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::NewProp_MapPath = { "MapPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LobbyGameMode_eventStartGame_Parms, MapPath), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::NewProp_MapPath,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ALobbyGameMode, nullptr, "StartGame", nullptr, nullptr, Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::PropPointers), sizeof(Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::LobbyGameMode_eventStartGame_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::Function_MetaDataParams), Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::LobbyGameMode_eventStartGame_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ALobbyGameMode_StartGame()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ALobbyGameMode_StartGame_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ALobbyGameMode::execStartGame)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_MapPath);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartGame(Z_Param_MapPath);
	P_NATIVE_END;
}
// End Class ALobbyGameMode Function StartGame

// Begin Class ALobbyGameMode
void ALobbyGameMode::StaticRegisterNativesALobbyGameMode()
{
	UClass* Class = ALobbyGameMode::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "StartGame", &ALobbyGameMode::execStartGame },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ALobbyGameMode);
UClass* Z_Construct_UClass_ALobbyGameMode_NoRegister()
{
	return ALobbyGameMode::StaticClass();
}
struct Z_Construct_UClass_ALobbyGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "LobbyGameMode.h" },
		{ "ModuleRelativePath", "Public/LobbyGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ALobbyGameMode_StartGame, "StartGame" }, // 1013415281
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ALobbyGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ALobbyGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AMultiplayerGameMode,
	(UObject* (*)())Z_Construct_UPackage__Script_BerkushsMultiplayerBase,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ALobbyGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ALobbyGameMode_Statics::ClassParams = {
	&ALobbyGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ALobbyGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ALobbyGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ALobbyGameMode()
{
	if (!Z_Registration_Info_UClass_ALobbyGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ALobbyGameMode.OuterSingleton, Z_Construct_UClass_ALobbyGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ALobbyGameMode.OuterSingleton;
}
template<> BERKUSHSMULTIPLAYERBASE_API UClass* StaticClass<ALobbyGameMode>()
{
	return ALobbyGameMode::StaticClass();
}
ALobbyGameMode::ALobbyGameMode() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ALobbyGameMode);
ALobbyGameMode::~ALobbyGameMode() {}
// End Class ALobbyGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_LobbyGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ALobbyGameMode, ALobbyGameMode::StaticClass, TEXT("ALobbyGameMode"), &Z_Registration_Info_UClass_ALobbyGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ALobbyGameMode), 1960157944U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_LobbyGameMode_h_2412587528(TEXT("/Script/BerkushsMultiplayerBase"),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_LobbyGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_LobbyGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
