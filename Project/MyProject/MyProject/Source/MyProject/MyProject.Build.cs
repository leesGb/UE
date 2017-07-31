// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

/**
 * @reference https://wiki.unrealengine.com/Animation_Node,_Translate_With_Complete_Source_Code_and_Instructions
 */

public class MyProject : ModuleRules
{
	public MyProject(TargetInfo Target)
	{
        // �������� VS �����еİ���Ŀ¼��ͷ�ļ������������ЩĿ¼��
        // Engine\Plugins\Developer\BlankPlugin\Source\BlankPlugin\BlankPlugin.Build.cs
        PrivateIncludePaths.AddRange(
            new string[] {
                // Player ����
                "MyProject/Private/MyEngine",
                "MyProject/Private/MyEngine/UI/Widgets",
                "MyProject/Private/MyEngine/Persist",
                "MyProject/Private/MyEngine/MyActor",
                "MyProject/Private/MyEngine/Math",
                "MyProject/Private/MyEngine/Misc",
                "MyProject/Private/MyEngine/Network",
                "MyProject/Private/MyEngine/Network/Web",
                "MyProject/Private/MyEngine/MyAsset",
                "MyProject/Private/MyEngine/AI",
                "MyProject/Private/MyEngine/MyBluePrint",
                
                "MyProject/Private/MyEngine/MyBase",
                "MyProject/Private/MyEngine/MyBase/Actor",
                "MyProject/Private/MyEngine/MyBase/Frame",
                "MyProject/Private/MyEngine/MyBase/AI",
                "MyProject/Private/MyEngine/MyBase/Anim",
                "MyProject/Private/MyEngine/MyBase/Delegate",
                "MyProject/Private/MyEngine/MyBase/Misc",
				"MyProject/Private/MyEngine/MyBase/HAL",
				"MyProject/Private/MyEngine/MyBase/Tick",

                "MyProject/Private/MyEngine/MyFly",
                "MyProject/Private/MyEngine/MyFly/Actor",
                "MyProject/Private/MyEngine/MyFly/Frame",
                "MyProject/Private/MyEngine/MyFly/AI",
                "MyProject/Private/MyEngine/MyFly/Anim",

                "MyProject/Private/MyEngine/MyTP",
                "MyProject/Private/MyEngine/MyTP/Actor",
                "MyProject/Private/MyEngine/MyTP/Frame",
                "MyProject/Private/MyEngine/MyTP/AI",
                "MyProject/Private/MyEngine/MyTP/Anim",

                // Libs ����
                "MyProject/Private/BasicFrame/Libs/Common",
                "MyProject/Private/BasicFrame/Libs/DataStruct",
                "MyProject/Private/BasicFrame/Libs/EngineWrap",
                "MyProject/Private/BasicFrame/Libs/FrameWork",
                "MyProject/Private/BasicFrame/Libs/NetWork/Socket",
                "MyProject/Private/BasicFrame/Libs/NetWork/Cmd",
                "MyProject/Private/BasicFrame/Libs/NetWork/Web",

                "MyProject/Private/BasicFrame/Libs/UI/UICore",
                "MyProject/Private/BasicFrame/Libs/UI/UIWidget",
                "MyProject/Private/BasicFrame/Libs/UI/UIWidget/TreeWidget",

                "MyProject/Private/BasicFrame/Libs/Log",
                "MyProject/Private/BasicFrame/Libs/Table",
                "MyProject/Private/BasicFrame/Libs/Table/ItemObject",
                "MyProject/Private/BasicFrame/Libs/Util",

                "MyProject/Private/BasicFrame/Libs/Thread",
                "MyProject/Private/BasicFrame/Libs/FastDelegate",
                "MyProject/Private/BasicFrame/Libs/Tools",
                "MyProject/Private/BasicFrame/Libs/DelayHandle",
                "MyProject/Private/BasicFrame/Libs/EventHandle",
                "MyProject/Private/BasicFrame/Libs/FrameHandle",

                "MyProject/Private/BasicFrame/Libs/Resource/ResLoad",
                "MyProject/Private/BasicFrame/Libs/Resource/ResLoad/LoadItem",
                "MyProject/Private/BasicFrame/Libs/Resource/ResLoad/ResourceItem",
                "MyProject/Private/BasicFrame/Libs/Resource/ResLoadData",
                "MyProject/Private/BasicFrame/Libs/Resource/RefAsync",
                "MyProject/Private/BasicFrame/Libs/Resource/InsResMgr",
                "MyProject/Private/BasicFrame/Libs/Resource/InsRes",
                "MyProject/Private/BasicFrame/Libs/Resource/Download",
                "MyProject/Private/BasicFrame/Libs/Resource/DelayTask",

                "MyProject/Private/BasicFrame/Libs/ObjectPool",
                "MyProject/Private/BasicFrame/Libs/MsgRoute",
                "MyProject/Private/BasicFrame/Libs/FileSystem",
                "MyProject/Private/BasicFrame/Libs/Math",
                "MyProject/Private/BasicFrame/Libs/Task",
                "MyProject/Private/BasicFrame/Libs/Core",
                "MyProject/Private/BasicFrame/Libs/Core/Object",
                "MyProject/Private/BasicFrame/Libs/Core/Templates",
                "MyProject/Private/BasicFrame/Libs/Core/Rtti",
                "MyProject/Private/BasicFrame/Libs/Core/Platform",
                "MyProject/Private/BasicFrame/Libs/Core/Memory",
                "MyProject/Private/BasicFrame/Libs/Core/Tools",

                "MyProject/Private/BasicFrame/Libs/LuaBind",
                "MyProject/Private/BasicFrame/Libs/LuaCppInterface",
                "MyProject/Private/BasicFrame/Libs/LuaCBridge",
                "MyProject/Private/BasicFrame/Libs/Module",
                "MyProject/Private/BasicFrame/Libs/Scene",

                "MyProject/Private/BasicFrame/Libs/Auxiliary/AuxLoader",
                "MyProject/Private/BasicFrame/Libs/Auxiliary/AuxUI",

                "MyProject/Private/BasicFrame/Module",
                "MyProject/Private/BasicFrame/Module/Game",
                "MyProject/Private/BasicFrame/Module/Game/EventCB",

                // UI ����
                "MyProject/Private/BasicFrame/UI/UIPack",
                "MyProject/Private/BasicFrame/UI/UITestCanvas",
                "MyProject/Private/BasicFrame/UI/UICustomButton",
                "MyProject/Private/BasicFrame/UI/UILoadStyles",
                "MyProject/Private/BasicFrame/UI/UIChat",
                "MyProject/Private/BasicFrame/UI/UILog",
                "MyProject/Private/BasicFrame/UI/UIEditText",
                "MyProject/Private/BasicFrame/UI/UISlateTab",
                "MyProject/Private/BasicFrame/UI/UISlateStyleSet",
                "MyProject/Private/BasicFrame/UI/UITestUMG",
                "MyProject/Private/BasicFrame/UI/UIFunctionBar",

                // Test ����
                "MyProject/Private/BasicFrame/UnitTest",
                "MyProject/Private/BasicFrame/UnitTest/TestBase",
                "MyProject/Private/BasicFrame/UnitTest/TestUI",
                "MyProject/Private/BasicFrame/UnitTest/TestDownload",
                "MyProject/Private/BasicFrame/UnitTest/TestNetClientBuffer",
                "MyProject/Private/BasicFrame/UnitTest/TestOther",
                "MyProject/Private/BasicFrame/UnitTest/TestLuaBind",

                // Example
                "MyProject/Private/BasicFrame/Example/AccessMesh",
                "MyProject/Private/BasicFrame/Example/AnimateVertexPositions",
                "MyProject/Private/BasicFrame/Example/AnimationCppAndBlueprint",
                "MyProject/Private/BasicFrame/Example/AnimNode",

                "MyProject/Private/BasicFrame/Example/AsyncLoad",
                "MyProject/Private/BasicFrame/Example/ClearWidgets",
                "MyProject/Private/BasicFrame/Example/CoordinateMapping",
                "MyProject/Private/BasicFrame/Example/CppAndBlueprint",

                "MyProject/Private/BasicFrame/Example/CustomActorIcon",
                "MyProject/Private/BasicFrame/Example/CustomComponents",
                "MyProject/Private/BasicFrame/Example/DeferAttachToSocket",
                "MyProject/Private/BasicFrame/Example/DelegatesInCppBP",

                "MyProject/Private/BasicFrame/Example/DistanceToCollision",
                "MyProject/Private/BasicFrame/Example/DynamicLoadObject",
                "MyProject/Private/BasicFrame/Example/EnumToString",
                "MyProject/Private/BasicFrame/Example/EventHand",

                "MyProject/Private/BasicFrame/Example/ExtendUserWidget",
                "MyProject/Private/BasicFrame/Example/FileAndPath",
                "MyProject/Private/BasicFrame/Example/InterfaceImpl",
                "MyProject/Private/BasicFrame/Example/LogMacro",

                "MyProject/Private/BasicFrame/Example/ModularPawn",
                "MyProject/Private/BasicFrame/Example/MultiThread",
                "MyProject/Private/BasicFrame/Example/ObjectIterator",
                "MyProject/Private/BasicFrame/Example/ObjectLibraryLoad",

                "MyProject/Private/BasicFrame/Example/RWConfigFile",
                "MyProject/Private/BasicFrame/Example/SubclassAccess",
                "MyProject/Private/BasicFrame/Example/TaskGraphSystem",
                "MyProject/Private/BasicFrame/Example/UmgExtendInCpp",

                "MyProject/Private/BasicFrame/Example/UmgInCpp",
            }
        );

        PublicIncludePaths.AddRange(
            new string[] {
                "MyProject/Public/MyEngine",
                "MyProject/Public/MyEngine/Player",
                "MyProject/Public/MyEngine/UI",
                "MyProject/Public/MyEngine/Persist",
            }
        );

        // ������Ҫ������ Public ģ�飬����ͷ�ļ�Ŀ¼�����ļ�Ŀ¼�Ϳ��ļ�����
        PublicDependencyModuleNames.AddRange(
            new string[] { 
                "Core", 
                "CoreUObject", 
                "Engine",
                "EngineSettings",   // UGameMapsSettings
                "OnlineSubsystem",
				"OnlineSubsystemUtils",
                "Sockets",
                "Networking",
                "UMG",
                "PhysX",    // PhysX
                "APEX",     // PhysX
                "SandboxFile",  // IPlatformFileSandboxWrapper.h���������Ӳ���
                //"DesktopPlatform", // IDesktopPlatform.h��ע���ƶ�ƽ̨��Ҫע�͵�

                //"UnrealEd", // UUnrealEdEngine \ UEditorEngine
            }
        );

        // ������Ҫ������ Private ģ�飬����ͷ�ļ�Ŀ¼�����ļ�Ŀ¼�Ϳ��ļ�����
        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",  // CoreUObject\Private\Serialization\AsyncLoadingThread.h
                "InputCore",
				"Slate",
				"SlateCore",
                "UMG",
                "HTTP",
            }
        );

        // AnimGraphRuntime ģ��İ���Ŀ¼��Ҫ�������룬�ο� Engine.Build.cs
        DynamicallyLoadedModuleNames.Add("AnimGraphRuntime");

        // ���� Private ģ���е�ͷ�ļ�Ŀ¼
        //PrivateIncludePathModuleNames.AddRange(
        //    new string[] {
        //        "HTTP"
        //    }
        //);

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            Definitions.Add("_CRT_SECURE_NO_WARNINGS");
            Definitions.Add("__WIN32__");
        }
        //Definitions.Add("WIN32_LEAN_AND_MEAN");
        //Definitions.Add("_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH");
        //Definitions.Add("NO_GETADDRINFO");
        //Definitions.Add("ENABLE_EXCEPTIONS");
        //Definitions.Add("ENABLE_DETACH");

        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

        //PrivateIncludePaths.AddRange(
        //    new string[] {
        //        "Coupling/Private",
        //        // ... add other private include paths required here ...
        //        Path.Combine(ThirdPartyPath, "v8", "include"),
        //    }
        //);

        //PublicDependencyModuleNames.AddRange(
        //    new string[]
        //    {
        //        "Engine",
        //        "Core",
        //        // ... add other public dependencies that you statically link with here ...
        //    }
        //);

        //PrivateDependencyModuleNames.AddRange(
        //    new string[]
        //    {
        //        // ... add private dependencies that you statically link with here ...
        //    }
        //);

        //DynamicallyLoadedModuleNames.AddRange(
        //    new string[]
        //    {
        //        // ... add any modules that your module loads dynamically here ...
        //    }
        //);

        // ���ӶԵ������� PhysX_3.4 ������ͷ�ļ�
        AddEngineThirdPartyPrivateStaticDependencies(Target,
            "PhysX",
            "APEX"
            );
        //PublicSystemIncludePaths.Add("ThirdParty/hlslcc/hlslcc/src/hlslcc_lib");
        //RuntimeDependencies.Add(new RuntimeDependency("$(EngineDir)/Binaries/ThirdParty/ARM/Win32/astcenc.exe"));
        //string APEXDir = UEBuildConfiguration.UEThirdPartySourceDirectory + "PhysX/" + ApexVersion + "/";

        //if (UEBuildConfiguration.bBuildEditor == true)
        //{

        //    PublicDependencyModuleNames.AddRange(
        //        new string[] {
        //            "MyProjectEditor"
        //        }
        //    );

        //    CircularlyReferencedDependentModules.AddRange(
        //        new string[] {
        //            "MyProjectEditor",
        //        }
        //    );
        //}

        //LoadMyProjectEditor(Target);

        loadThirdPartyInclude();
        //LoadSockets(Target);
        LoadTestExtern(Target);
        //LoadGtest(Target);
        LoadLua(Target);
        LoadLuaSocket(Target);
    }

    /// <summary>
    /// Accessor for the Module's path
    /// </summary>
    protected string ModulePath
    {
        get
        {
            // ��UnrealBuildTool.RulesCompiler.GetModuleFilename(string)���ѹ�ʱ:��GetModuleFilename is deprecated, use the ModuleDirectory property on any ModuleRules instead to get a path to your module.��
            //return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name));
            //return Path.GetDirectoryName(ModuleDirectory);    // ����������ȡ
            return ModuleDirectory;      // ���� Engine\Plugins\Runtime\Nvidia\Ansel\Source\Ansel\Ansel.Build.cs ʵ��
        }
    }

    /// <summary>
    /// Accessor for thee ThirdParty Path.
    /// </summary>
    protected string ThirdPartyPath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModulePath, "../..", "ThirdParty"));
        }
    }

    private void loadThirdPartyInclude()
    {
        PublicIncludePaths.AddRange(
            new string[] 
            {
                // ... add public include paths required here ...
                Path.Combine(ThirdPartyPath, "Inc"),
                Path.Combine(ThirdPartyPath, "Inc", "Lua"),
                Path.Combine(ThirdPartyPath, "Inc", "LuaBridge"),
                Path.Combine(ThirdPartyPath, "Inc", "LuaSocket"),
            }
        );
    }

    // https://wiki.unrealengine.com/Linking_Static_Libraries_Using_The_Build_System
    private bool LoadSockets_bak(TargetInfo Target)
    {
        // https://wiki.unrealengine.com/Integrating_OpenCV_Into_Unreal_Engine_4
        bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug && BuildConfiguration.bDebugBuildsActuallyUseDebugCRT;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            //string PlatformString;
            string LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "Sockets");

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                //PlatformString = "x64";
                //LibrariesPath = Path.Combine(LibrariesPath, "Win64");

                if (Target.Configuration == UnrealTargetConfiguration.Debug)
                {
                    LibrariesPath = Path.Combine(LibrariesPath, "Debug");
                }
            }
            else
            {
                //PlatformString = "ia32";
                //LibrariesPath = Path.Combine(LibrariesPath, "Win32");
            }

            //LibrariesPath = Path.Combine(LibrariesPath, "Debug");

            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "icui18n.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "icuuc.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_base.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_libbase.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_nosnapshot.lib"));
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_snapshot.lib"));

            //PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "v8", "Includes"));

            //Definitions.Add(string.Format("WITH_COUPLING=1"));

            if (Target.Configuration == UnrealTargetConfiguration.Debug)
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Sockets.lib"));

                //Add Dynamic Libraries (Debug Version)
                //PublicDelayLoadDLLs.Add("opencv_world300d.dll");
            }
            else
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Sockets.lib"));
            }

            return true;
        }

        //Definitions.Add(string.Format("WITH_COUPLING=0"));
        return false;
    }

    private bool LoadSockets(TargetInfo Target)
    {
        string LibrariesPath;

        LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "Sockets", "Sockets_d.lib");
        PublicAdditionalLibraries.Add(LibrariesPath);

        return true;
    }

    private bool LoadTestExtern(TargetInfo Target)
    {
        string LibrariesPath;
        LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "TestStaticLib", "TestStaticLib_d.lib");

        PublicAdditionalLibraries.Add(LibrariesPath);

        return true;
    }

    private bool LoadGtest(TargetInfo Target)
    {
        string LibrariesPath;

        LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "gtest", "gtest_d.lib");
        PublicAdditionalLibraries.Add(LibrariesPath);

        return true;
    }

    // ���� Lua
    private bool LoadLua(TargetInfo Target)
    {
        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            string LibrariesPath;
            LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "Lua", "Lua_d.lib");
            PublicAdditionalLibraries.Add(LibrariesPath);
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);

            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(BuildPath, "My_APL_armv7.xml")));

            PublicAdditionalLibraries.Add(BuildPath + "/armv7/libLua.so");
        }

        return true;
    }

    private bool LoadLuaSocket(TargetInfo Target)
    {
        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            string LibrariesPath;
            LibrariesPath = Path.Combine(ThirdPartyPath, "Lib", "LuaSocket", "LuaSocket_d.lib");
            PublicAdditionalLibraries.Add(LibrariesPath);
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            string BuildPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);

            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(BuildPath, "My_APL_armv7.xml")));

            PublicAdditionalLibraries.Add(BuildPath + "/armv7/libLuaSocket.so");
        }

        return true;
    }

    // ���� ProjectEditor
    private bool LoadMyProjectEditor(TargetInfo Target)
    {
        if (UEBuildConfiguration.bBuildEditor == true)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "MyProjectEditor"
                }
            );

            CircularlyReferencedDependentModules.AddRange(
                new string[] {
                    "MyProjectEditor",
                }
            );
        }

        return true;
    }
}