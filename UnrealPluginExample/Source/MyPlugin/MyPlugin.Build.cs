// Copyright Epic Games, Inc. All Rights Reserved.


using System;
using System.IO;
using UnrealBuildTool;

public class MyPlugin : ModuleRules
{
	public MyPlugin(ReadOnlyTargetRules Target) : base(Target)
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
                Path.Combine(ModuleDirectory, "..", "..", "Deps", "include")
            }
			);
		
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "..", "Deps", "lib", "MvrGdtf-MD.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "..", "Deps", "lib", "xerces-c_3.lib"));
            PublicAdditionalLibraries.Add("Shlwapi.lib");
        }
        else
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "..", "Deps", "lib", "libMvrGdtf.a"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "..", "Deps", "lib", "libxerces-c-3.2.a"));
        }

        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
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
