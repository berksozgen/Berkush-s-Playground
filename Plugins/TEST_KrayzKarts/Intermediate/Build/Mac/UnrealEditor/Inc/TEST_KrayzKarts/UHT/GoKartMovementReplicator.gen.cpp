// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TEST_KrayzKarts/Public/GoKartMovementReplicator.h"
#include "TEST_KrayzKarts/Public/GoKartMovingComponent.h"
#include "UObject/CoreNet.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGoKartMovementReplicator() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
TEST_KRAYZKARTS_API UClass* Z_Construct_UClass_UGoKartMovementReplicator();
TEST_KRAYZKARTS_API UClass* Z_Construct_UClass_UGoKartMovementReplicator_NoRegister();
TEST_KRAYZKARTS_API UClass* Z_Construct_UClass_UGoKartMovingComponent_NoRegister();
TEST_KRAYZKARTS_API UScriptStruct* Z_Construct_UScriptStruct_FGoKartMove();
TEST_KRAYZKARTS_API UScriptStruct* Z_Construct_UScriptStruct_FGoKartState();
UPackage* Z_Construct_UPackage__Script_TEST_KrayzKarts();
// End Cross Module References

// Begin ScriptStruct FGoKartState
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GoKartState;
class UScriptStruct* FGoKartState::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GoKartState.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GoKartState.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGoKartState, (UObject*)Z_Construct_UPackage__Script_TEST_KrayzKarts(), TEXT("GoKartState"));
	}
	return Z_Registration_Info_UScriptStruct_GoKartState.OuterSingleton;
}
template<> TEST_KRAYZKARTS_API UScriptStruct* StaticStruct<FGoKartState>()
{
	return FGoKartState::StaticStruct();
}
struct Z_Construct_UScriptStruct_FGoKartState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Transform_MetaData[] = {
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastMove_MetaData[] = {
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Transform;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LastMove;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGoKartState>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGoKartState_Statics::NewProp_Transform = { "Transform", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGoKartState, Transform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Transform_MetaData), NewProp_Transform_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGoKartState_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGoKartState, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FGoKartState_Statics::NewProp_LastMove = { "LastMove", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGoKartState, LastMove), Z_Construct_UScriptStruct_FGoKartMove, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastMove_MetaData), NewProp_LastMove_MetaData) }; // 226844282
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGoKartState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGoKartState_Statics::NewProp_Transform,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGoKartState_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGoKartState_Statics::NewProp_LastMove,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGoKartState_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGoKartState_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TEST_KrayzKarts,
	nullptr,
	&NewStructOps,
	"GoKartState",
	Z_Construct_UScriptStruct_FGoKartState_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGoKartState_Statics::PropPointers),
	sizeof(FGoKartState),
	alignof(FGoKartState),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGoKartState_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FGoKartState_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FGoKartState()
{
	if (!Z_Registration_Info_UScriptStruct_GoKartState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GoKartState.InnerSingleton, Z_Construct_UScriptStruct_FGoKartState_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_GoKartState.InnerSingleton;
}
// End ScriptStruct FGoKartState

// Begin Class UGoKartMovementReplicator Function OnRep_ServerState
struct Z_Construct_UFunction_UGoKartMovementReplicator_OnRep_ServerState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGoKartMovementReplicator_OnRep_ServerState_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGoKartMovementReplicator, nullptr, "OnRep_ServerState", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGoKartMovementReplicator_OnRep_ServerState_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGoKartMovementReplicator_OnRep_ServerState_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UGoKartMovementReplicator_OnRep_ServerState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGoKartMovementReplicator_OnRep_ServerState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGoKartMovementReplicator::execOnRep_ServerState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_ServerState();
	P_NATIVE_END;
}
// End Class UGoKartMovementReplicator Function OnRep_ServerState

// Begin Class UGoKartMovementReplicator Function Server_SendMove
struct GoKartMovementReplicator_eventServer_SendMove_Parms
{
	FGoKartMove Move;
};
static FName NAME_UGoKartMovementReplicator_Server_SendMove = FName(TEXT("Server_SendMove"));
void UGoKartMovementReplicator::Server_SendMove(FGoKartMove Move)
{
	GoKartMovementReplicator_eventServer_SendMove_Parms Parms;
	Parms.Move=Move;
	ProcessEvent(FindFunctionChecked(NAME_UGoKartMovementReplicator_Server_SendMove),&Parms);
}
struct Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Move;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics::NewProp_Move = { "Move", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GoKartMovementReplicator_eventServer_SendMove_Parms, Move), Z_Construct_UScriptStruct_FGoKartMove, METADATA_PARAMS(0, nullptr) }; // 226844282
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics::NewProp_Move,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGoKartMovementReplicator, nullptr, "Server_SendMove", nullptr, nullptr, Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics::PropPointers), sizeof(GoKartMovementReplicator_eventServer_SendMove_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x80240CC1, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics::Function_MetaDataParams) };
static_assert(sizeof(GoKartMovementReplicator_eventServer_SendMove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGoKartMovementReplicator::execServer_SendMove)
{
	P_GET_STRUCT(FGoKartMove,Z_Param_Move);
	P_FINISH;
	P_NATIVE_BEGIN;
	if (!P_THIS->Server_SendMove_Validate(Z_Param_Move))
	{
		RPC_ValidateFailed(TEXT("Server_SendMove_Validate"));
		return;
	}
	P_THIS->Server_SendMove_Implementation(Z_Param_Move);
	P_NATIVE_END;
}
// End Class UGoKartMovementReplicator Function Server_SendMove

// Begin Class UGoKartMovementReplicator Function SetMeshOffsetRoot
struct Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics
{
	struct GoKartMovementReplicator_eventSetMeshOffsetRoot_Parms
	{
		USceneComponent* Root;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GoKartMovementReplicator_eventSetMeshOffsetRoot_Parms, Root), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::NewProp_Root,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGoKartMovementReplicator, nullptr, "SetMeshOffsetRoot", nullptr, nullptr, Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::GoKartMovementReplicator_eventSetMeshOffsetRoot_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::GoKartMovementReplicator_eventSetMeshOffsetRoot_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGoKartMovementReplicator::execSetMeshOffsetRoot)
{
	P_GET_OBJECT(USceneComponent,Z_Param_Root);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetMeshOffsetRoot(Z_Param_Root);
	P_NATIVE_END;
}
// End Class UGoKartMovementReplicator Function SetMeshOffsetRoot

// Begin Class UGoKartMovementReplicator
void UGoKartMovementReplicator::StaticRegisterNativesUGoKartMovementReplicator()
{
	UClass* Class = UGoKartMovementReplicator::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnRep_ServerState", &UGoKartMovementReplicator::execOnRep_ServerState },
		{ "Server_SendMove", &UGoKartMovementReplicator::execServer_SendMove },
		{ "SetMeshOffsetRoot", &UGoKartMovementReplicator::execSetMeshOffsetRoot },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGoKartMovementReplicator);
UClass* Z_Construct_UClass_UGoKartMovementReplicator_NoRegister()
{
	return UGoKartMovementReplicator::StaticClass();
}
struct Z_Construct_UClass_UGoKartMovementReplicator_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "GoKartMovementReplicator.h" },
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerState_MetaData[] = {
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovingComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshOffsetRoot_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GoKartMovementReplicator.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ServerState;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MovingComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MeshOffsetRoot;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGoKartMovementReplicator_OnRep_ServerState, "OnRep_ServerState" }, // 936403202
		{ &Z_Construct_UFunction_UGoKartMovementReplicator_Server_SendMove, "Server_SendMove" }, // 1039314262
		{ &Z_Construct_UFunction_UGoKartMovementReplicator_SetMeshOffsetRoot, "SetMeshOffsetRoot" }, // 1857818042
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGoKartMovementReplicator>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGoKartMovementReplicator_Statics::NewProp_ServerState = { "ServerState", "OnRep_ServerState", (EPropertyFlags)0x0040000100000020, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGoKartMovementReplicator, ServerState), Z_Construct_UScriptStruct_FGoKartState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerState_MetaData), NewProp_ServerState_MetaData) }; // 509334704
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGoKartMovementReplicator_Statics::NewProp_MovingComponent = { "MovingComponent", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGoKartMovementReplicator, MovingComponent), Z_Construct_UClass_UGoKartMovingComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovingComponent_MetaData), NewProp_MovingComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGoKartMovementReplicator_Statics::NewProp_MeshOffsetRoot = { "MeshOffsetRoot", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGoKartMovementReplicator, MeshOffsetRoot), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshOffsetRoot_MetaData), NewProp_MeshOffsetRoot_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGoKartMovementReplicator_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGoKartMovementReplicator_Statics::NewProp_ServerState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGoKartMovementReplicator_Statics::NewProp_MovingComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGoKartMovementReplicator_Statics::NewProp_MeshOffsetRoot,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGoKartMovementReplicator_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGoKartMovementReplicator_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_TEST_KrayzKarts,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGoKartMovementReplicator_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGoKartMovementReplicator_Statics::ClassParams = {
	&UGoKartMovementReplicator::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGoKartMovementReplicator_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGoKartMovementReplicator_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGoKartMovementReplicator_Statics::Class_MetaDataParams), Z_Construct_UClass_UGoKartMovementReplicator_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGoKartMovementReplicator()
{
	if (!Z_Registration_Info_UClass_UGoKartMovementReplicator.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGoKartMovementReplicator.OuterSingleton, Z_Construct_UClass_UGoKartMovementReplicator_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGoKartMovementReplicator.OuterSingleton;
}
template<> TEST_KRAYZKARTS_API UClass* StaticClass<UGoKartMovementReplicator>()
{
	return UGoKartMovementReplicator::StaticClass();
}
void UGoKartMovementReplicator::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static const FName Name_ServerState(TEXT("ServerState"));
	const bool bIsValid = true
		&& Name_ServerState == ClassReps[(int32)ENetFields_Private::ServerState].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UGoKartMovementReplicator"));
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGoKartMovementReplicator);
UGoKartMovementReplicator::~UGoKartMovementReplicator() {}
// End Class UGoKartMovementReplicator

// Begin Registration
struct Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FGoKartState::StaticStruct, Z_Construct_UScriptStruct_FGoKartState_Statics::NewStructOps, TEXT("GoKartState"), &Z_Registration_Info_UScriptStruct_GoKartState, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGoKartState), 509334704U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGoKartMovementReplicator, UGoKartMovementReplicator::StaticClass, TEXT("UGoKartMovementReplicator"), &Z_Registration_Info_UClass_UGoKartMovementReplicator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGoKartMovementReplicator), 2690287158U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_766967073(TEXT("/Script/TEST_KrayzKarts"),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
