// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DeadByDaylight/Survivor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSurvivor() {}
// Cross Module References
	DEADBYDAYLIGHT_API UClass* Z_Construct_UClass_ASurvivor_NoRegister();
	DEADBYDAYLIGHT_API UClass* Z_Construct_UClass_ASurvivor();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_DeadByDaylight();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
	DEADBYDAYLIGHT_API UClass* Z_Construct_UClass_USurvivorAnimInstance_NoRegister();
	DEADBYDAYLIGHT_API UClass* Z_Construct_UClass_USurvivorStatComponent_NoRegister();
// End Cross Module References
	void ASurvivor::StaticRegisterNativesASurvivor()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASurvivor);
	UClass* Z_Construct_UClass_ASurvivor_NoRegister()
	{
		return ASurvivor::StaticClass();
	}
	struct Z_Construct_UClass_ASurvivor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SphereCollision_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SphereCollision;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SurvivorAnimInstance_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SurvivorAnimInstance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Stat_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Stat;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Hp_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Hp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WalkSpeed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_WalkSpeed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RunSpeed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_RunSpeed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bRunning_MetaData[];
#endif
		static void NewProp_bRunning_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bRunning;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bInteracting_MetaData[];
#endif
		static void NewProp_bInteracting_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bInteracting;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bCarried_MetaData[];
#endif
		static void NewProp_bCarried_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bCarried;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bHanged_MetaData[];
#endif
		static void NewProp_bHanged_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bHanged;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bTraped_MetaData[];
#endif
		static void NewProp_bTraped_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bTraped;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASurvivor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_DeadByDaylight,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Survivor.h" },
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Survivor.h" },
		{ "ToolTip", "Camera boom positioning the camera behind the character" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASurvivor, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_CameraBoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_CameraBoom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "Comment", "/** Follow camera */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Survivor.h" },
		{ "ToolTip", "Follow camera" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASurvivor, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_FollowCamera_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_FollowCamera_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_SphereCollision_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Coponents" },
		{ "Comment", "// ?????? \xc4\xa1?? ???? ????\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Survivor.h" },
		{ "ToolTip", "?????? \xc4\xa1?? ???? ????" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_SphereCollision = { "SphereCollision", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASurvivor, SphereCollision), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_SphereCollision_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_SphereCollision_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_SurvivorAnimInstance_MetaData[] = {
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_SurvivorAnimInstance = { "SurvivorAnimInstance", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASurvivor, SurvivorAnimInstance), Z_Construct_UClass_USurvivorAnimInstance_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_SurvivorAnimInstance_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_SurvivorAnimInstance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_Stat_MetaData[] = {
		{ "Category", "Survivor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_Stat = { "Stat", nullptr, (EPropertyFlags)0x00400000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASurvivor, Stat), Z_Construct_UClass_USurvivorStatComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_Stat_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_Stat_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_Hp_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Stat" },
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_Hp = { "Hp", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASurvivor, Hp), METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_Hp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_Hp_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_WalkSpeed_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_WalkSpeed = { "WalkSpeed", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASurvivor, WalkSpeed), METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_WalkSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_WalkSpeed_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_RunSpeed_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_RunSpeed = { "RunSpeed", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASurvivor, RunSpeed), METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_RunSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_RunSpeed_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_bRunning_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
	void Z_Construct_UClass_ASurvivor_Statics::NewProp_bRunning_SetBit(void* Obj)
	{
		((ASurvivor*)Obj)->bRunning = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_bRunning = { "bRunning", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASurvivor), &Z_Construct_UClass_ASurvivor_Statics::NewProp_bRunning_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_bRunning_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_bRunning_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_bInteracting_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
	void Z_Construct_UClass_ASurvivor_Statics::NewProp_bInteracting_SetBit(void* Obj)
	{
		((ASurvivor*)Obj)->bInteracting = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_bInteracting = { "bInteracting", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASurvivor), &Z_Construct_UClass_ASurvivor_Statics::NewProp_bInteracting_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_bInteracting_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_bInteracting_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_bCarried_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
	void Z_Construct_UClass_ASurvivor_Statics::NewProp_bCarried_SetBit(void* Obj)
	{
		((ASurvivor*)Obj)->bCarried = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_bCarried = { "bCarried", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASurvivor), &Z_Construct_UClass_ASurvivor_Statics::NewProp_bCarried_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_bCarried_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_bCarried_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_bHanged_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
	void Z_Construct_UClass_ASurvivor_Statics::NewProp_bHanged_SetBit(void* Obj)
	{
		((ASurvivor*)Obj)->bHanged = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_bHanged = { "bHanged", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASurvivor), &Z_Construct_UClass_ASurvivor_Statics::NewProp_bHanged_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_bHanged_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_bHanged_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASurvivor_Statics::NewProp_bTraped_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "Survivor.h" },
	};
#endif
	void Z_Construct_UClass_ASurvivor_Statics::NewProp_bTraped_SetBit(void* Obj)
	{
		((ASurvivor*)Obj)->bTraped = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASurvivor_Statics::NewProp_bTraped = { "bTraped", nullptr, (EPropertyFlags)0x0040000000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ASurvivor), &Z_Construct_UClass_ASurvivor_Statics::NewProp_bTraped_SetBit, METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::NewProp_bTraped_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::NewProp_bTraped_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASurvivor_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_CameraBoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_FollowCamera,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_SphereCollision,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_SurvivorAnimInstance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_Stat,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_Hp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_WalkSpeed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_RunSpeed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_bRunning,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_bInteracting,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_bCarried,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_bHanged,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASurvivor_Statics::NewProp_bTraped,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASurvivor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASurvivor>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASurvivor_Statics::ClassParams = {
		&ASurvivor::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ASurvivor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ASurvivor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASurvivor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASurvivor()
	{
		if (!Z_Registration_Info_UClass_ASurvivor.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASurvivor.OuterSingleton, Z_Construct_UClass_ASurvivor_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASurvivor.OuterSingleton;
	}
	template<> DEADBYDAYLIGHT_API UClass* StaticClass<ASurvivor>()
	{
		return ASurvivor::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASurvivor);
	struct Z_CompiledInDeferFile_FID_DeadByDaylight_Source_DeadByDaylight_Survivor_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DeadByDaylight_Source_DeadByDaylight_Survivor_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASurvivor, ASurvivor::StaticClass, TEXT("ASurvivor"), &Z_Registration_Info_UClass_ASurvivor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASurvivor), 4141724695U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DeadByDaylight_Source_DeadByDaylight_Survivor_h_3267575597(TEXT("/Script/DeadByDaylight"),
		Z_CompiledInDeferFile_FID_DeadByDaylight_Source_DeadByDaylight_Survivor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DeadByDaylight_Source_DeadByDaylight_Survivor_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
