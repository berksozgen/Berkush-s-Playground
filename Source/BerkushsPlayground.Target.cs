// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BerkushsPlaygroundTarget : TargetRules
{
	public BerkushsPlaygroundTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("BerkushsPlayground");
		
		//lobalDefinitions.Add("UE_PROJECT_STEAMSHIPPINGID=2989320");
	}
}
