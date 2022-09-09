// Some copyright should be here...

using UnrealBuildTool;
using System.IO;
public class OSGBLibrary : ModuleRules
{
	public OSGBLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseRTTI = true;
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
		string tt = ModuleDirectory;
		string OSGBPath = Path.Combine(ModuleDirectory, "../../../../ThirdParty/OSG");
		string IncDir = Path.Combine(OSGBPath, "include");
		string LibDir = Path.Combine(OSGBPath, "lib");
		string DllDir = Path.Combine(OSGBPath, "bin");
		string DllDir2 = Path.Combine(DllDir, "osgPlugins-3.6.5");
		PublicIncludePaths.Add(IncDir);
		foreach (string file in Directory.GetFiles(LibDir))
		{
			PublicAdditionalLibraries.Add(Path.Combine(LibDir, file));
		}
	}
}
