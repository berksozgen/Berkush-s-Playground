// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GoKartMovementReplicator.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USceneComponent;
struct FGoKartMove;
#ifdef TEST_KRAYZKARTS_GoKartMovementReplicator_generated_h
#error "GoKartMovementReplicator.generated.h already included, missing '#pragma once' in GoKartMovementReplicator.h"
#endif
#define TEST_KRAYZKARTS_GoKartMovementReplicator_generated_h

#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_15_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FGoKartState_Statics; \
	TEST_KRAYZKARTS_API static class UScriptStruct* StaticStruct();


template<> TEST_KRAYZKARTS_API UScriptStruct* StaticStruct<struct FGoKartState>();

#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_45_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual bool Server_SendMove_Validate(FGoKartMove ); \
	virtual void Server_SendMove_Implementation(FGoKartMove Move); \
	DECLARE_FUNCTION(execOnRep_ServerState); \
	DECLARE_FUNCTION(execServer_SendMove); \
	DECLARE_FUNCTION(execSetMeshOffsetRoot);


#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_45_CALLBACK_WRAPPERS
#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_45_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGoKartMovementReplicator(); \
	friend struct Z_Construct_UClass_UGoKartMovementReplicator_Statics; \
public: \
	DECLARE_CLASS(UGoKartMovementReplicator, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TEST_KrayzKarts"), NO_API) \
	DECLARE_SERIALIZER(UGoKartMovementReplicator) \
	NO_API void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ServerState=NETFIELD_REP_START, \
		NETFIELD_REP_END=ServerState	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_45_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UGoKartMovementReplicator(UGoKartMovementReplicator&&); \
	UGoKartMovementReplicator(const UGoKartMovementReplicator&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGoKartMovementReplicator); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGoKartMovementReplicator); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGoKartMovementReplicator) \
	NO_API virtual ~UGoKartMovementReplicator();


#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_42_PROLOG
#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_45_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_45_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_45_CALLBACK_WRAPPERS \
	FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_45_INCLASS_NO_PURE_DECLS \
	FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h_45_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TEST_KRAYZKARTS_API UClass* StaticClass<class UGoKartMovementReplicator>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_TEST_KrayzKarts_Source_TEST_KrayzKarts_Public_GoKartMovementReplicator_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
