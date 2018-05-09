// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

/**
 * @brief �Լ��ֹ������Ѿ��еĲ����Ȼ�������Ϊ MyScriptGeneratorPlugin ���������Ǳ�����˵�Ҳ������ MyScriptGeneratorPlugin ��Ȼ���Լ�ͨ�� UE4Editor -- Editor -- Plugins -- ����һ��ͬ�����ֵĲ����Ȼ��ԭ���� MyScriptGeneratorPlugin ���ݿ�������������ͱ���ͨ���ˣ���ְ�
 */
public class MyScriptGeneratorPlugin : ModuleRules
{
	public MyScriptGeneratorPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"MyScriptGeneratorPlugin/Public",
                "Programs/UnrealHeaderTool/Public",     // IScriptGeneratorPluginInterface
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"MyScriptGeneratorPlugin/Private",
                "Developer/ScriptGeneratorPlugin/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
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
                "Projects",
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