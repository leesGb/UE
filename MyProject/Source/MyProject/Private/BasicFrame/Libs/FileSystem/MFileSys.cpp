﻿#include "MyProject.h"
#include "MFileSys.h"
#include "FContainers/UnrealString.h"		// FString
#include "HAL/PlatformFilemanager.h"	   // FPlatformFileManager

std::string MFileSys::msPersistentDataPath = "";
std::string MFileSys::msStreamingAssetsPath = "";

MFileSys::MFileSys()
{
	// 初始化 SandBox 文件系统
	this->mSandboxPlatformFile = new FSandboxPlatformFile(false);
}

void MFileSys::init()
{
	// 初始化 SandBox 文件系统
	//mSandboxPlatformFile = new FSandboxPlatformFile(false);
	//FString OutputDirectory = GetOutputDirectoryOverride();
	FString OutputDirectory = FPaths::GameDir();
	this->mSandboxPlatformFile->Initialize(&FPlatformFileManager::Get().GetPlatformFile(), *FString::Printf(TEXT("-sandbox=\"%s\""), *OutputDirectory));

	MFileSys::initFileSys();
}

void MFileSys::dispose()
{
	delete this->mSandboxPlatformFile;
}

FSandboxPlatformFile* MFileSys::getSandboxPlatformFile()
{
	return this->mSandboxPlatformFile;
}

void MFileSys::initFileSys()
{

}

// 获取本地可以读取的目录，但是不能写
std::string MFileSys::getLocalReadDir()
{
	return "";
}

// 获取本地可以写的目录
std::string MFileSys::getLocalWriteDir()
{
	return mPersistentDataPath;
}

void MFileSys::modifyLoadParam(std::string resPath, LoadParam* param)
{
//#if PKG_RES_LOAD
//	param.mOrigPath = resPath;             // 记录原始的资源名字
//
//	string retPath = resPath;
//
//	if ("Module/AutoUpdate.prefab" == resPath)       // 自动更新模块更新还没有实现
//	{
//		param.mResLoadType = ResLoadType.eStreamingAssets;
//	}
//	else
//	{
//		// 获取包的名字
//		if (Ctx.m_instance.m_pPakSys.path2PakDic.ContainsKey(resPath))
//		{
//			retPath = Ctx.m_instance.m_pPakSys.path2PakDic[resPath].m_pakName;
//		}
//
//		if (param != null)
//		{
//			Ctx.m_instance.m_localFileSys.getAbsPathByRelPath(ref retPath, ref param.mResLoadType);
//		}
//		else
//		{
//			ResLoadType tmp = ResLoadType.eStreamingAssets;
//			Ctx.m_instance.m_localFileSys.getAbsPathByRelPath(ref retPath, ref tmp);
//		}
//	}
//	param.mPath = retPath;
//	param.mPakPath = param.mPath;
//#elif UnPKG_RES_LOAD
//	if (param != null)
//	{
//		param.mResLoadType = ResLoadType.eStreamingAssets;
//	}
//	param.mPath = resPath;
//#else
//	param.mPath = resPath;
//#endif
}