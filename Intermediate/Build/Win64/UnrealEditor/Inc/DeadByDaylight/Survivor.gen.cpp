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
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASurvivor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASurvivor>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASurvivor_Statics::ClassParams = {
		&ASurvivor::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
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
		{ Z_Construct_UClass_ASurvivor, ASurvivor::StaticClass, TEXT("ASurvivor"), &Z_Registration_Info_UClass_ASurvivor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASurvivor), 2837200447U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DeadByDaylight_Source_DeadByDaylight_Survivor_h_2415584969(TEXT("/Script/DeadByDaylight"),
		Z_CompiledInDeferFile_FID_DeadByDaylight_Source_DeadByDaylight_Survivor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DeadByDaylight_Source_DeadByDaylight_Survivor_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
