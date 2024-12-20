// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MultiplayerGameInstance.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef BERKUSHSMULTIPLAYERBASE_MultiplayerGameInstance_generated_h
#error "MultiplayerGameInstance.generated.h already included, missing '#pragma once' in MultiplayerGameInstance.h"
#endif
#define BERKUSHSMULTIPLAYERBASE_MultiplayerGameInstance_generated_h

#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execJoin); \
	DECLARE_FUNCTION(execHost); \
	DECLARE_FUNCTION(execInGameLoadMenu); \
	DECLARE_FUNCTION(execLoadMenuWidget);


#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMultiplayerGameInstance(); \
	friend struct Z_Construct_UClass_UMultiplayerGameInstance_Statics; \
public: \
	DECLARE_CLASS(UMultiplayerGameInstance, UGameInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/BerkushsMultiplayerBase"), NO_API) \
	DECLARE_SERIALIZER(UMultiplayerGameInstance) \
	virtual UObject* _getUObject() const override { return const_cast<UMultiplayerGameInstance*>(this); }


#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_19_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UMultiplayerGameInstance(UMultiplayerGameInstance&&); \
	UMultiplayerGameInstance(const UMultiplayerGameInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMultiplayerGameInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMultiplayerGameInstance); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMultiplayerGameInstance) \
	NO_API virtual ~UMultiplayerGameInstance();


#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_16_PROLOG
#define FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_19_INCLASS_NO_PURE_DECLS \
	FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> BERKUSHSMULTIPLAYERBASE_API UClass* StaticClass<class UMultiplayerGameInstance>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_berksozgen_Documents_Unreal_Projects_BerkushsPlayground_Plugins_BerkushsMultiplayerBase_Source_BerkushsMultiplayerBase_Public_MultiplayerGameInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
