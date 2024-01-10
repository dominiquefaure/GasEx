// Copyright 2023 Dominique Faure. All Rights Reserved.

using UnrealBuildTool;

public class GasExEditor : ModuleRules
{
	public GasExEditor(ReadOnlyTargetRules Target) : base(Target)
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
				"Persona",
				"GasEx",
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
