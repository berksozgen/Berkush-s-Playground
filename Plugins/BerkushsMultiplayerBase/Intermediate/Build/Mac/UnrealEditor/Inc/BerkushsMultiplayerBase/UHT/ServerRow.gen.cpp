// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BerkushsMultiplayerBase/MenuSystem/ServerRow.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeServerRow() {}

// Begin Cross Module References
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UMainMenu_NoRegister();
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UServerRow();
BERKUSHSMULTIPLAYERBASE_API UClass* Z_Construct_UClass_UServerRow_NoRegister();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UTextBlock_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_BerkushsMultiplayerBase();
// End Cross Module References

// Begin Class UServerRow Function OnClicked
struct Z_Construct_UFunction_UServerRow_OnClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MenuSystem/ServerRow.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UServerRow_OnClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UServerRow, nullptr, "OnClicked", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UServerRow_OnClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_UServerRow_OnClicked_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UServerRow_OnClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UServerRow_OnClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UServerRow::execOnClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnClicked();
	P_NATIVE_END;
}
// End Class UServerRow Function OnClicked

// Begin Class UServerRow
void UServerRow::StaticRegisterNativesUServerRow()
{
	UClass* Class = UServerRow::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnClicked", &UServerRow::execOnClicked },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UServerRow);
UClass* Z_Construct_UClass_UServerRow_NoRegister()
{
	return UServerRow::StaticClass();
}
struct Z_Construct_UClass_UServerRow_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "MenuSystem/ServerRow.h" },
		{ "ModuleRelativePath", "MenuSystem/ServerRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerName_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MenuSystem/ServerRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HostUser_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MenuSystem/ServerRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ConnectionFraction_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MenuSystem/ServerRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsSelected_MetaData[] = {
		{ "Category", "ServerRow" },
		{ "ModuleRelativePath", "MenuSystem/ServerRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RowButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MenuSystem/ServerRow.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Parent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MenuSystem/ServerRow.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ServerName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HostUser;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ConnectionFraction;
	static void NewProp_bIsSelected_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsSelected;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RowButton;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Parent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UServerRow_OnClicked, "OnClicked" }, // 1473312564
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UServerRow>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UServerRow_Statics::NewProp_ServerName = { "ServerName", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UServerRow, ServerName), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerName_MetaData), NewProp_ServerName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UServerRow_Statics::NewProp_HostUser = { "HostUser", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UServerRow, HostUser), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HostUser_MetaData), NewProp_HostUser_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UServerRow_Statics::NewProp_ConnectionFraction = { "ConnectionFraction", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UServerRow, ConnectionFraction), Z_Construct_UClass_UTextBlock_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ConnectionFraction_MetaData), NewProp_ConnectionFraction_MetaData) };
void Z_Construct_UClass_UServerRow_Statics::NewProp_bIsSelected_SetBit(void* Obj)
{
	((UServerRow*)Obj)->bIsSelected = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UServerRow_Statics::NewProp_bIsSelected = { "bIsSelected", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UServerRow), &Z_Construct_UClass_UServerRow_Statics::NewProp_bIsSelected_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsSelected_MetaData), NewProp_bIsSelected_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UServerRow_Statics::NewProp_RowButton = { "RowButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UServerRow, RowButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RowButton_MetaData), NewProp_RowButton_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UServerRow_Statics::NewProp_Parent = { "Parent", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UServerRow, Parent), Z_Construct_UClass_UMainMenu_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Parent_MetaData), NewProp_Parent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UServerRow_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UServerRow_Statics::NewProp_ServerName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UServerRow_Statics::NewProp_HostUser,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UServerRow_Statics::NewProp_ConnectionFraction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UServerRow_Statics::NewProp_bIsSelected,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UServerRow_Statics::NewProp_RowButton,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UServerRow_Statics::NewProp_Parent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UServerRow_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UServerRow_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_BerkushsMultiplayerBase,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UServerRow_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UServerRow_Statics::ClassParams = {
	&UServerRow::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UServerRow_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UServerRow_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UServerRow_Statics::Class_MetaDataParams), Z_Construct_UClass_UServerRow_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UServerRow()
{
	if (!Z_Registration_Info_UClass_UServerRow.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UServerRow.OuterSingleton, Z_Construct_UClass_UServerRow_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UServerRow.OuterSingleton;
}
template<> BERKUSHSMULTIPLAYERBASE_API UClass* StaticClass<UServerRow>()
{
	return UServerRow::StaticClass();
}
UServerRow::UServerRow(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UServerRow);
UServerRow::~UServerRow() {}
// End Class UServerRow

// Begin Registration
struct Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_ServerRow_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UServerRow, UServerRow::StaticClass, TEXT("UServerRow"), &Z_Registration_Info_UClass_UServerRow, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UServerRow), 2143478174U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_ServerRow_h_3056852260(TEXT("/Script/BerkushsMultiplayerBase"),
	Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_ServerRow_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_MenuSystem_ServerRow_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
