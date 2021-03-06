using UnrealBuildTool;
 
public class MyProjectEditor : ModuleRules
{
    //public MyProjectEditor(TargetInfo Target)
    // 4.17
    public MyProjectEditor(ReadOnlyTargetRules Target) : base(Target)
    {
		// To compile this module without implicit precompiled headers, add "PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;" to MyProject.build.cs.
		// UE4 4.17 之前没加这一行，结果总是不能生成 UE4Editor-MyProjectEditor-Win64-Debug.dll ，添加这一行就可以生成 UE4Editor-MyProjectEditor-Win64-Debug.dll 了
        this.PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // warning CS0618: “UnrealBuildTool.ModuleRules.Definitions”已过时:“The 'Definitions' property has been deprecated. Please use 'PublicDefinitions' instead.”
        //this.Definitions.Add("MY_WITH_EDITOR");
        this.PublicDefinitions.Add("MY_WITH_EDITOR");

        //PrivateIncludePaths.Add("MyProjectEditor/Private");
        PrivateIncludePaths.AddRange(
			new string[] 
            {
                // Main area
                "MyProjectEditor/Private/MyEngine",
                "MyProjectEditor/Private/MyEngine/Animation",
                "MyProjectEditor/Private/MyEngine/MyBase",
                "MyProjectEditor/Private/MyEngine/MyAsset",

                // Example area
                "MyProjectEditor/Private/MyEngine/AnimNode",
                "MyProjectEditor/Private/MyEngine/Example/CppAndBlueprint"
            }
		);

        PublicIncludePaths.AddRange(
            new string[] 
            {
                "MyProjectEditor/Public/MyEngine"
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",

                "AnimGraph",

                "UnrealEd", // UUnrealEdEngine \ UEditorEngine
                "BlueprintGraph",
                "GraphEditor",
                "PropertyEditor",
                "SlateCore",
                "Slate",
                "EditorStyle",
                "Kismet",
                "KismetCompiler",

                "AnimGraphRuntime",
                "AnimationEditor",
                "GeometryMode",
                //"MyProject"
            }
        );
 
        PrivateDependencyModuleNames.AddRange(
            new string[] 
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",

                "UnrealEd", // UUnrealEdEngine \ UEditorEngine
                "BlueprintGraph",
                "AnimGraph",

                "GraphEditor",
                "PropertyEditor",
                "SlateCore",
                "Slate",
                "EditorStyle",
                "Kismet",
                "KismetCompiler",

                "AnimGraphRuntime",
                "GeometryMode",
                //"MyProject"
            }
        );

        // AnimGraphRuntime 模块的包含目录需要这样导入，参考 Engine.Build.cs
       // DynamicallyLoadedModuleNames.Add("AnimGraphRuntime");
        //DynamicallyLoadedModuleNames.AddRange(
        //    new string[] 
        //    {
        //        "AnimGraphRuntime"
        //    }
        //);

        // Engine\Plugins\Editor\SpeedTreeImporter\Source\SpeedTreeImporter\SpeedTreeImporter.Build.cs
        //AddEngineThirdPartyPrivateStaticDependencies(Target, "SpeedTree");

        // https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
        // You'll probably also want to add "MyCodeProject" to the PublicDependencyModuleNames in your MyCodeProjectEditor.Build.cs file, as this will allow your editor module access to your game code.
        //PublicDependencyModuleNames.AddRange(
        //    new string[] 
        //    {
        //        "MyProject"
        //    }
        //);

        //CircularlyReferencedDependentModules.AddRange(
        //    new string[] 
        //    {
        //        "MyProject",
        //    }
        //);
    }
}