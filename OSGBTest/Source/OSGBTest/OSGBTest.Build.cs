// Fill out your copyright notice in the Description page of Project Settings.
using UnrealBuildTool;
using System.IO;

public class OSGBTest : ModuleRules
{
	public OSGBTest(ReadOnlyTargetRules Target) : base(Target)
	{
		bUseRTTI = true;
		bEnableExceptions = true;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ProceduralMeshComponent", "EditorScriptingUtilities" });

		PrivateDependencyModuleNames.AddRange(new string[] { "EditorScriptingUtilities" });
		string OSGBPath = Path.Combine(ModuleDirectory, "../../ThirdParty/OSG");
		string IncDir = Path.Combine(OSGBPath, "include");
		string LibDir = Path.Combine(OSGBPath, "lib");
		PublicIncludePaths.Add(IncDir);
		foreach (string file in Directory.GetFiles(LibDir))
		{
			if(!file.Contains("pkgconfig"))
            {
				PublicAdditionalLibraries.Add(Path.Combine(LibDir, file));
			}
		}
		//foreach (string file in Directory.GetFiles(LibDir2))
		//{
		//	PublicAdditionalLibraries.Add(Path.Combine(LibDir2, file));
		//}
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
