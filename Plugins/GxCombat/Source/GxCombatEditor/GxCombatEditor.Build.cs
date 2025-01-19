// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

using UnrealBuildTool;

public class GxCombatEditor : ModuleRules
{
	public GxCombatEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
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
				"AssetTools",
				"GameplayAbilitiesEditor",
				"GraphEditor",
				"EnhancedInput",
				"InputCore",
				"GxCombat",
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
				"ComponentVisualizers"
			}
			);

		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"DataTableEditor",
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
