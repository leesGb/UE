﻿#include "MyProject.h"
#include "LocalVer.h"
#include "MDataStream.h"
#include "MyMemoryInc.h"
#include "ResLoadType.h"
#include "IDispatchObject.h"
#include "FileVerInfo.h"
#include "MDataStream.h"
#include "MFileSystem.h"
#include "UtilFileIO.h"
#include "LogInc.h"
#include "VerFileName.h"
#include "MiscInc.h"
#include "MacroDef.h"
#include "EventDispatchDelegate.h"
#include "MiscInc.h"
#include "AddOnceAndCallOnceEventDispatch.h"
#include "UtilStr.h"

MY_BEGIN_NAMESPACE(MyNS)

LocalVer::LocalVer()
{
	// 本地必然加载成功，因为只有打包的时候才会有 VerFileName 这些文件，不打包的时候是没有 VerFileName 这些配置文件的，因此统一处理成必然加载成功
	this->mIsMiniLoadSuccess = true;
	this->mIsVerLoadSuccess = true;

	this->mIsMiniLoaded = false;
	this->mIsVerSLoaded = false;
	this->mIsVerPLoaded = false;
}

void LocalVer::loadAllLocalVer()
{
	this->loadMiniVerFile();
	//this->loadLocalRVer();
	this->loadLocalSVer();
	this->loadLocalPVer();
}

std::string LocalVer::getInstallVersionString()
{
	std::string ret = "";

	ret = UtilStr::Format("{0}-{1}-{2}", this->mInstallMajorVersion, this->mInstallMinorVersion, this->mInstallPatchVersion);

	return ret;
}

void LocalVer::loadMiniVerFile()
{
	//if (MacroDef::ENABLE_LOG)
	//{
	//    GLogSys->log("LocalVer::loadMiniVerFile, Persistent", LogTypeId::eLogAutoUpdate);
	//}

	//// 先从 PersistentPath 目录下读取,各个平台都可以同步读取
	//this->mMiniDataStream = new MDataStream(UtilFileIO::combine(MFileSystem::msDataStreamPersistentDataPath, VerFileName::VER_MINI), this->onPersistentMiniLoadEventHandle);
	//this->mMiniDataStream.open();

	//// 如果读取没有成功，就从 StreamingAssetsPath (不再从 Resources) 目录下读取， StreamingAssetsPath android 下读取非 AssetBundles 需要异步
	//if (this->mFileVerInfo->isNoVerInfo())
	//{
	//    if (MacroDef::ENABLE_LOG)
	//    {
	//        GLogSys->log("LocalVer::loadMiniVerFile, StreamingAssets", LogTypeId::eLogAutoUpdate);
	//    }

	//    this->mIsMiniLoaded = false;     // 重新设置成 false ，防止后面的因为异步加载完成后，再调用一次的时候，会调用外面两次

	//    //this->mMiniDataStream = new MDataStream(UtilFileIO::combine(MFileSystem::msDataStreamResourcesPath, "Constant", VerFileName::VER_MINI), this->onMiniLoadEventHandle);
	//    this->mMiniDataStream = new MDataStream(UtilFileIO::combine(MFileSystem::msDataStreamStreamingAssetsPath, VerFileName::VER_MINI), this->onStreamingMiniLoadEventHandle);
	//    this->mMiniDataStream.open();
	//}

	////this->mMiniLoadedDispatch->dispatchEvent(nullptr);

	this->loadStreamingAssetsMiniVerFile();
}

void LocalVer::loadStreamingAssetsMiniVerFile()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("LocalVer::loadStreamingAssetsMiniVerFile, StreamingAssets", LogTypeId::eLogAutoUpdate);
	}

	this->mIsMiniLoaded = false;     // 重新设置成 false ，防止后面的因为异步加载完成后，再调用一次的时候，会调用外面两次

	//this->mMiniDataStream = new MDataStream(UtilFileIO::combine(MFileSystem::msDataStreamResourcesPath, "Constant", VerFileName::VER_MINI), this->onMiniLoadEventHandle);
	this->mMiniDataStream = MY_NEW MDataStream(
		UtilFileIO::combine(
			MFileSystem::msDataStreamStreamingAssetsPath, 
			VerFileName::VER_MINI
		), 
		MakeEventDispatchDelegate(
			this, 
			&LocalVer::onStreamingMiniLoadEventHandle, 
			(uint)0
		)
	);
	this->mMiniDataStream->open();
}

void LocalVer::loadPersistentMiniVerFile()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("LocalVer::loadPersistentMiniVerFile, Persistent", LogTypeId::eLogAutoUpdate);
	}

	// 先从 PersistentPath 目录下读取,各个平台都可以同步读取
	this->mMiniDataStream = MY_NEW MDataStream(
		UtilFileIO::combine(
			MFileSystem::msDataStreamPersistentDataPath, 
			VerFileName::VER_MINI
		), 
		MakeEventDispatchDelegate(
			this,
			&LocalVer::onPersistentMiniLoadEventHandle,
			(uint)0
		)
	);
	this->mMiniDataStream->open();
}

void LocalVer::onStreamingMiniLoadEventHandle(uint eventId, IDispatchObject* dispObj)
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("LocalVer::onStreamingMiniLoadEventHandle", LogTypeId::eLogAutoUpdate);
	}

	this->onMiniLoadEventHandle(0, dispObj);

	this->mInstallMajorVersion = this->mMajorVersion;
	this->mInstallMinorVersion = this->mMinorVersion;
	this->mInstallPatchVersion = this->mPatchVersion;

	// 检查清理本地更新保存的文件
	GAutoClearSys->checkAutoClear();

	this->loadPersistentMiniVerFile();
}

void LocalVer::onPersistentMiniLoadEventHandle(uint eventId, IDispatchObject* dispObj)
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("LocalVer::onPersistentMiniLoadEventHandle", LogTypeId::eLogAutoUpdate);
	}

	this->onMiniLoadEventHandle(0, dispObj);

	// 设置本地加载完成标志
	this->mIsMiniLoaded = true;
	this->_onAllVerLoaded();
}

void LocalVer::onMiniLoadEventHandle(uint eventId, IDispatchObject* dispObj)
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("LocalVer::onMiniLoadEventHandle", LogTypeId::eLogAutoUpdate);
	}

	this->mMiniDataStream = (MDataStream*)dispObj;

	if (this->mMiniDataStream->isValid())
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("LocalVer::onMiniLoadEventHandle, success", LogTypeId::eLogAutoUpdate);
		}

		this->parseMiniFile(this->mMiniDataStream->readText());
	}

	this->mMiniDataStream->dispose();
	this->mMiniDataStream = nullptr;

	//this->mMiniLoadedDispatch->dispatchEvent(nullptr);

	//this->mIsMiniLoaded = true;
	//this->onAllVerLoaded();
}

// 加载 Resources 文件夹下文件对应的版本系统，目前没有了
void LocalVer::loadLocalRVer()
{
	std::string param = "Constant";

	this->mRDataStream = MY_NEW MDataStream(
		UtilFileIO::combine(
			MFileSystem::msDataStreamResourcesPath, 
			param,
			VerFileName::VER_R
		), 
		MakeEventDispatchDelegate(
			this,
			&LocalVer::onRVerLoaded,
			(uint)0
		)
	);
	this->mRDataStream->open();
}

void LocalVer::onRVerLoaded(uint eventId, IDispatchObject* dispObj)
{
	this->mRDataStream = (MDataStream*)dispObj;

	if (this->mRDataStream->isValid())
	{
		this->_loadFormText(this->mRDataStream->readText(), this->mPath2Ver_R_Dic, this->mABPath2Ver_R_Dic);
	}

	this->mRDataStream->dispose();
	this->mRDataStream = nullptr;

	this->_onAllVerLoaded();
}

// Android 下 StreamingAssets 目录访问只能是异步的，因此需要等待这个访问完成才行
void LocalVer::loadLocalSVer()
{
	std::string path = UtilFileIO::combine(MFileSystem::msDataStreamStreamingAssetsPath, VerFileName::VER_S);

	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log(UtilStr::Format("LocalVer::loadLocalSVer, path = {0}", path), LogTypeId::eLogAutoUpdate);
	}

	// 不要从 StreamingAssets 这个目录下加载 VerFileName::VER_S ，因为在 Android 上是异步加载的，因此直接放在 Resources 目录下，但是现在是不再向 Resources 目录下，本地都放在 StreamingAssets 目录

	this->mSDataStream = MY_NEW MDataStream(
		path, 
		MakeEventDispatchDelegate(
			this,
			&LocalVer::onSVerLoaded,
			(uint)0
		)
	);
	//this->mSDataStream = new MDataStream(UtilFileIO::combine(MFileSystem::msDataStreamResourcesPath, "Constant", VerFileName::VER_S), this->onSVerLoaded);
	this->mSDataStream->open();
}

void LocalVer::onSVerLoaded(uint eventId, IDispatchObject* dispObj)
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("LocalVer::onSVerLoaded", LogTypeId::eLogAutoUpdate);
	}

	this->mSDataStream = (MDataStream*)dispObj;

	if (this->mSDataStream->isValid())
	{
		std::string text = this->mSDataStream->readText();

		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log(UtilStr::Format("LocalVer::onSVerLoaded, success, text = {0}", text), LogTypeId::eLogAutoUpdate);
		}

		//this->mSDataStream.seek(0, MSeekOrigin.eBegin);
		this->_loadFormText(text, this->mPath2Ver_S_Dic, this->mABPath2Ver_S_Dic);
	}

	this->mSDataStream->dispose();
	this->mSDataStream = nullptr;

	this->mIsVerSLoaded = true;
	this->_onAllVerLoaded();
}

void LocalVer::loadLocalPVer()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("LocalVer::loadLocalPVer", LogTypeId::eLogAutoUpdate);
	}

	this->mPDataStream = MY_NEW MDataStream(
		UtilFileIO::combine(
			MFileSystem::msDataStreamPersistentDataPath, 
			VerFileName::VER_P
		), 
		MakeEventDispatchDelegate(
			this,
			&LocalVer::onPVerLoaded,
			(uint)0
		)
	);
	this->mPDataStream->open();
}

void LocalVer::onPVerLoaded(uint eventId, IDispatchObject* dispObj)
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("LocalVer::onPVerLoaded", LogTypeId::eLogAutoUpdate);
	}

	this->mPDataStream = (MDataStream*)dispObj;

	if (this->mPDataStream->isValid())
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("LocalVer::onPVerLoaded, success", LogTypeId::eLogAutoUpdate);
		}

		this->_loadFormText(this->mPDataStream->readText(), this->mPath2Ver_P_Dic, this->mABPath2Ver_P_Dic);
	}

	this->mPDataStream->dispose();
	this->mPDataStream = nullptr;

	this->mIsVerPLoaded = true;
	this->_onAllVerLoaded();
}

void LocalVer::_onAllVerLoaded()
{
	if (this->mIsMiniLoaded && this->mIsVerSLoaded && this->mIsVerPLoaded)
	{
		this->mLoadedDispatch->dispatchEvent(nullptr);
		//Ctx.msInstance.setIsLocalVerLoaded(true);
	}
}

int LocalVer::getFileVerInfo(std::string& origPath, FileVerInfo* fileVerInfo, bool isABAsset)
{
	// 在 Resources 中资源是大写，在 AssetBundles 中包含的资源名字是小写，但是 StreamingAssets 或者 Persistent 中不是 AssetBundles 形式的资源，仍然是大写
	UtilStr::toLower(origPath);
	std::string lowerOrigPath = origPath;
	std::string md5 = "";
	ResLoadType resLoadType = ResLoadType::eLoadResource;

	if (!isABAsset)
	{
		resLoadType = ResLoadType::eLoadResource;

		// 这个目录只要有就记录，例如 Windows.unity3d 这种 manifest 文件就是大写的，其它的资源目录都是小写的，为了兼容，检查大写和小写
		if (this->mPath2Ver_P_Dic.containsKey(origPath))
		{
			this->_analyzeHash(this->mPath2Ver_P_Dic[origPath], ResLoadType::eLoadLocalPersistentData, fileVerInfo, md5, resLoadType);
		}
		else if (this->mPath2Ver_P_Dic.containsKey(lowerOrigPath))
		{
			this->_analyzeHash(this->mPath2Ver_P_Dic[lowerOrigPath], ResLoadType::eLoadLocalPersistentData, fileVerInfo, md5, resLoadType);
		}

		if (this->mPath2Ver_S_Dic.containsKey(origPath))
		{
			// 如果两个 Hash 码是相同，就说明资源定向在 StreamAsset 目录里面
			this->_analyzeHash(this->mPath2Ver_S_Dic[origPath], ResLoadType::eLoadStreamingAssets, fileVerInfo, md5, resLoadType);
		}
		else if (this->mPath2Ver_S_Dic.containsKey(lowerOrigPath))
		{
			this->_analyzeHash(this->mPath2Ver_S_Dic[lowerOrigPath], ResLoadType::eLoadStreamingAssets, fileVerInfo, md5, resLoadType);
		}

		if (this->mPath2Ver_R_Dic.containsKey(origPath))
		{
			this->_analyzeHash(this->mPath2Ver_R_Dic[origPath], ResLoadType::eLoadResource, fileVerInfo, md5, resLoadType);
		}
	}
	else
	{
		resLoadType = ResLoadType::eLoadStreamingAssets;

		// 这个目录只要有就记录
		if (this->mABPath2Ver_P_Dic.containsKey(lowerOrigPath))
		{
			this->_analyzeHash(this->mABPath2Ver_P_Dic[lowerOrigPath], ResLoadType::eLoadLocalPersistentData, fileVerInfo, md5, resLoadType);
		}
		else if (this->mABPath2Ver_P_Dic.containsKey(origPath))
		{
			this->_analyzeHash(this->mABPath2Ver_P_Dic[origPath], ResLoadType::eLoadLocalPersistentData, fileVerInfo, md5, resLoadType);
		}

		if (this->mABPath2Ver_S_Dic.containsKey(lowerOrigPath))
		{
			// 如果两个 Hash 码是相同，就说明资源定向在 StreamAsset 目录里面
			this->_analyzeHash(this->mABPath2Ver_S_Dic[lowerOrigPath], ResLoadType::eLoadStreamingAssets, fileVerInfo, md5, resLoadType);
		}
		else if (this->mABPath2Ver_S_Dic.containsKey(origPath))
		{
			this->_analyzeHash(this->mABPath2Ver_S_Dic[origPath], ResLoadType::eLoadStreamingAssets, fileVerInfo, md5, resLoadType);
		}
	}

	return (int)resLoadType;
}

// 比较 Hash 码
void LocalVer::_analyzeHash(
	FileVerInfo* srcFileVerInfo,
	ResLoadType defaultResLoadType,
	FileVerInfo* fileVerInfo,
	std::string& md5,
	ResLoadType resLoadType
)
{
	// else 就是不修改 fileVerInfo 信息
	if (md5 == srcFileVerInfo->mFileMd5)     // 如果有 md5 ，并且 md5 == srcFileVerInfo.mFileMd5 ，就返回 srcFileVerInfo
	{
		fileVerInfo = srcFileVerInfo;
		resLoadType = defaultResLoadType;
	}
	else if (UtilStr::IsNullOrEmpty(md5))     // 如果没有 md5 ，就返回 srcFileVerInfo
	{
		fileVerInfo = srcFileVerInfo;
		md5 = fileVerInfo->mFileMd5;
		resLoadType = defaultResLoadType;
	}
}

MY_END_NAMESPACE