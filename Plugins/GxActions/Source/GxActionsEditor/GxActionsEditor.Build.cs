// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GxActionsEditor : ModuleRules
{
	public GxActionsEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				"GxActions"
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
				"GameplayTags",
				"GameplayTasks",
				"GameplayAbilities",
				"GxCore",
				"GxActions"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"GameplayAbilities",
				"BlueprintGraph",
				"Kismet",
				"EditorStyle",
				"AnimGraphRuntime",
				"AnimGraph",
				"Projects",
				"MessageLog",
				"ApplicationCore",
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
