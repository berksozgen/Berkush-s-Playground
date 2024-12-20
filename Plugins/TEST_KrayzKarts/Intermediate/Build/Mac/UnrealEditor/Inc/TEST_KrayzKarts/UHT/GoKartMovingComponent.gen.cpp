// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TEST_KrayzKarts/Public/GoKartMovingComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGoKartMovingComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
TEST_KRAYZKARTS_API UClass* Z_Construct_UClass_UGoKartMovingComponent();
TEST_KRAYZKARTS_API UClass* Z_Construct_UClass_UGoKartMovingComponent_NoRegister();
TEST_KRAYZKARTS_API UScriptStruct* Z_Construct_UScriptStruct_FGoKartMove();
UPackage* Z_Construct_UPackage__Script_TEST_KrayzKarts();
// End Cross Module References

// Begin ScriptStruct FGoKartMove
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GoKartMove;
class UScriptStruct* FGoKartMove::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GoKartMove.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GoKartMove.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGoKartMove, (UObject*)Z_Construct_UPackage__Script_TEST_KrayzKarts(), TEXT("GoKartMove"));
	}
	return Z_Registration_Info_UScriptStruct_GoKartMove.OuterSingleton;
}
template<> TEST_KRAYZKARTS_API UScriptStruct* StaticStruct<FGoKartMove>()
{
	return FGoKartMove::StaticStruct();
}
struct Z_Construct_UScriptStruct_FGoKartMove_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Throttle_MetaData[] = {
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SteeringThrow_MetaData[] = {
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeltaTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Time_MetaData[] = {
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Throttle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SteeringThrow;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Time;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGoKartMove>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGoKartMove_Statics::NewProp_Throttle = { "Throttle", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGoKartMove, Throttle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Throttle_MetaData), NewProp_Throttle_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGoKartMove_Statics::NewProp_SteeringThrow = { "SteeringThrow", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGoKartMove, SteeringThrow), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SteeringThrow_MetaData), NewProp_SteeringThrow_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGoKartMove_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGoKartMove, DeltaTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeltaTime_MetaData), NewProp_DeltaTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FGoKartMove_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FGoKartMove, Time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Time_MetaData), NewProp_Time_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGoKartMove_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGoKartMove_Statics::NewProp_Throttle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGoKartMove_Statics::NewProp_SteeringThrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGoKartMove_Statics::NewProp_DeltaTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGoKartMove_Statics::NewProp_Time,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGoKartMove_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGoKartMove_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_TEST_KrayzKarts,
	nullptr,
	&NewStructOps,
	"GoKartMove",
	Z_Construct_UScriptStruct_FGoKartMove_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGoKartMove_Statics::PropPointers),
	sizeof(FGoKartMove),
	alignof(FGoKartMove),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGoKartMove_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FGoKartMove_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FGoKartMove()
{
	if (!Z_Registration_Info_UScriptStruct_GoKartMove.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GoKartMove.InnerSingleton, Z_Construct_UScriptStruct_FGoKartMove_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_GoKartMove.InnerSingleton;
}
// End ScriptStruct FGoKartMove

// Begin Class UGoKartMovingComponent
void UGoKartMovingComponent::StaticRegisterNativesUGoKartMovingComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGoKartMovingComponent);
UClass* Z_Construct_UClass_UGoKartMovingComponent_NoRegister()
{
	return UGoKartMovingComponent::StaticClass();
}
struct Z_Construct_UClass_UGoKartMovingComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "GoKartMovingComponent.h" },
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mass_MetaData[] = {
		{ "Category", "GoKartMovingComponent" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//The mass of the car (kg).\n" },
#endif
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The mass of the car (kg)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxDrivingForce_MetaData[] = {
		{ "Category", "GoKartMovingComponent" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//The force applied to the car when the throttle is fully down (N).\n" },
#endif
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The force applied to the car when the throttle is fully down (N)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinTurningRadius_MetaData[] = {
		{ "Category", "GoKartMovingComponent" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Minimum radius of the car turning circle at full lock (m).\n" },
#endif
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum radius of the car turning circle at full lock (m)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DragCoefficient_MetaData[] = {
		{ "Category", "GoKartMovingComponent" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Higher means more drag.\n" },
#endif
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Higher means more drag." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RollingResistanceCoefficient_MetaData[] = {
		{ "Category", "GoKartMovingComponent" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Higher means more Rolling Resistance.\n" },
#endif
		{ "ModuleRelativePath", "Public/GoKartMovingComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Higher means more Rolling Resistance." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Mass;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxDrivingForce;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinTurningRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DragCoefficient;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RollingResistanceCoefficient;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGoKartMovingComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGoKartMovingComponent_Statics::NewProp_Mass = { "Mass", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGoKartMovingComponent, Mass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mass_MetaData), NewProp_Mass_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGoKartMovingComponent_Statics::NewProp_MaxDrivingForce = { "MaxDrivingForce", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGoKartMovingComponent, MaxDrivingForce), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxDrivingForce_MetaData), NewProp_MaxDrivingForce_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGoKartMovingComponent_Statics::NewProp_MinTurningRadius = { "MinTurningRadius", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGoKartMovingComponent, MinTurningRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinTurningRadius_MetaData), NewProp_MinTurningRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGoKartMovingComponent_Statics::NewProp_DragCoefficient = { "DragCoefficient", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGoKartMovingComponent, DragCoefficient), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DragCoefficient_MetaData), NewProp_DragCoefficient_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGoKartMovingComponent_Statics::NewProp_RollingResistanceCoefficient = { "RollingResistanceCoefficient", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGoKartMovingComponent, RollingResistanceCoefficient), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RollingResistanceCoefficient_MetaData), NewProp_RollingResistanceCoefficient_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGoKartMovingComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGoKartMovingComponent_Statics::NewProp_Mass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGoKartMovingComponent_Statics::NewProp_MaxDrivingForce,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGoKartMovingComponent_Statics::NewProp_MinTurningRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGoKartMovingComponent_Statics::NewProp_DragCoefficient,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGoKartMovingComponent_Statics::NewProp_RollingResistanceCoefficient,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGoKartMovingComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGoKartMovingComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_TEST_KrayzKarts,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGoKartMovingComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGoKartMovingComponent_Statics::ClassParams = {
	&UGoKartMovingComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UGoKartMovingComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UGoKartMovingComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGoKartMovingComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UGoKartMovingComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGoKartMovingComponent()
{
	if (!Z_Registration_Info_UClass_UGoKartMovingComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGoKartMovingComponent.OuterSingleton, Z_Construct_UClass_UGoKartMovingComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGoKartMovingComponent.OuterSingleton;
}
template<> TEST_KRAYZKARTS_API UClass* StaticClass<UGoKartMovingComponent>()
{
	return UGoKartMovingComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGoKartMovingComponent);
UGoKartMovingComponent::~UGoKartMovingComponent() {}
// End Class UGoKartMovingComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovingComponent_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FGoKartMove::StaticStruct, Z_Construct_UScriptStruct_FGoKartMove_Statics::NewStructOps, TEXT("GoKartMove"), &Z_Registration_Info_UScriptStruct_GoKartMove, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGoKartMove), 226844282U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGoKartMovingComponent, UGoKartMovingComponent::StaticClass, TEXT("UGoKartMovingComponent"), &Z_Registration_Info_UClass_UGoKartMovingComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGoKartMovingComponent), 1217320939U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovingComponent_h_2280546373(TEXT("/Script/TEST_KrayzKarts"),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovingComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovingComponent_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovingComponent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovingComponent_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
