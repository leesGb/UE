#include "MyProject.h"
#include "UtilFileIO.h"
#include "Containers/UnrealString.h"
#include "Misc/Paths.h"
#include "Core.h"
#include "CoreGlobals.h"
#include "HAL/FileManager.h"		// IFileManager
#include "Prequisites.h"
#include "UtilStr.h"
#include "Symbolic.h"

MY_BEGIN_NAMESPACE(MyNS)

FString UtilFileIO::BaseDir()
{
	//InstallDir/WindowsNoEditor/GameName/Binaries/Win64
	const FString ThePath = FString(FPlatformProcess::BaseDir());
	return ThePath;
}

FString UtilFileIO::RootDir(bool isAbsPath)
{
	//InstallDir/WindowsNoEditor/
	FString ThePath;

	if (isAbsPath)
	{
		ThePath = FPaths::ConvertRelativePathToFull(FPaths::RootDir());
	}
	else
	{
		ThePath = FPaths::RootDir();
	}

	return ThePath;
}

FString UtilFileIO::GameDir(bool isAbsPath)
{
	// UE 4.19.1 warning C4996: 'FPaths::GameDir': FPaths::GameDir() has been superseded by FPaths::ProjectDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//InstallDir/WindowsNoEditor/GameName
	//const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameDir());
	FString ThePath;

	if (isAbsPath)
	{
		ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	}
	else
	{
		ThePath = FPaths::ProjectDir();
	}

	return ThePath;
}

FString UtilFileIO::GameContentDir(bool isAbsPath)
{
	// UE 4.19.1 warning C4996: 'FPaths::GameContentDir': FPaths::GameContentDir() has been superseded by FPaths::ProjectContentDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//InstallDir/WindowsNoEditor/GameName/Content
	//const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir());
	FString ThePath;

	if (isAbsPath)
	{
		ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	}
	else
	{
		ThePath = FPaths::ProjectContentDir();
	}

	return ThePath;
}

FString UtilFileIO::EngineContentDir(bool isAbsPath)
{
	FString ThePath;

	if(isAbsPath)
	{
		ThePath = FPaths::ConvertRelativePathToFull(FPaths::EngineContentDir());
	}
	else
	{
		ThePath = FPaths::EngineContentDir();
	}

	return ThePath;
}

FString UtilFileIO::GameSavedDir(bool isAbsPath)
{
	// UE 4.19.1 warning C4996: 'FPaths::GameSavedDir': FPaths::GameSavedDir() has been superseded by FPaths::ProjectSavedDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//InstallDir/WindowsNoEditor/GameName/Saved
	//const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir());
	FString ThePath;

	if (isAbsPath)
	{
		ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
	}
	else
	{
		ThePath = FPaths::ProjectSavedDir();
	}

	return ThePath;
}

FString UtilFileIO::GameLogDir(bool isAbsPath)
{
	// UE 4.19.1 warning C4996: 'FPaths::GameLogDir': FPaths::GameLogDir() has been superseded by FPaths::ProjectLogDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//InstallDir/WindowsNoEditor/GameName/Saved/Logs
	//const FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameLogDir());
	FString ThePath;

	if (isAbsPath)
	{
		ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectLogDir());
	}
	else
	{
		ThePath = FPaths::ProjectLogDir();
	}

	return ThePath;
}

FString UtilFileIO::GetFilenameOnDisk(FString FullFilename)
{
	IFileManager& FileManager = IFileManager::Get();
	FString DiskFilename = FileManager.GetFilenameOnDisk(*FullFilename);
	return DiskFilename;
}

FString UtilFileIO::ConvertToSandboxPath(FString FullFilename)
{
	//const FString ThePath = FPaths::ConvertToSandboxPath(FPaths::GameLogDir());
	//IFileManager& FileManager = IFileManager::Get();
	FString DiskFilename = GFileSysSandboxPlatformFile->ConvertToSandboxPath(*FullFilename);
	return DiskFilename;
}

FString UtilFileIO::FPaths_ConvertToSandboxPath(FString FullFilename)
{
	return FPaths::ConvertToSandboxPath(FullFilename, TEXT("aaaa"));
}

void UtilFileIO::NormalizeDirectoryName(FString& InPath)
{
	FPaths::NormalizeDirectoryName(InPath);
}

bool UtilFileIO::FileExists(const std::string& InPath)
{
	FString convPath = UtilStr::ConvStdStr2FString(const_cast<std::string&>(InPath));
	return FPaths::FileExists(convPath);
}

std::string UtilFileIO::combine(
	std::string& path0,
	std::string& path1,
	std::string& path2,
	std::string& path3
)
{
	std::string ret = "";

	if (path2.length() > 0 && path3.length() > 0)
	{
		ret = path0 + "/" + path1 + "/" + path2 + "/" + path3;
	}
	else if (path2.length() > 0)
	{
		ret = path0 + "/" + path1 + "/" + path2;
	}

	return ret;
}

bool UtilFileIO::existFile(std::string& fullFilPath)
{
	return FileExists(fullFilPath);
}

bool UtilFileIO::deleteFile(std::string& fullFilPath)
{
	IFileManager::Get().Delete(UtilStr::convStdStr2TCHAR(fullFilPath));
	return true;
}

// 获取扩展名
std::string UtilFileIO::getFileExt(std::string& path)
{
	std::string extName = "";

	int dotIdx = path.find_last_of('.');

	if (-1 != dotIdx)
	{
		extName = path.substr(dotIdx + 1);
	}

	return extName;
}

// 获取文件名字，没有路径，但是有扩展名字
std::string UtilFileIO::getFileNameWithExt(std::string& fullPath)
{
	int index = fullPath.find_last_of('/');
	std::string ret = "";

	if (index == -1)
	{
		index = fullPath.find_last_of('\\');
	}
	if (index != -1)
	{
		ret = fullPath.substr(index + 1);
	}
	else
	{
		ret = fullPath;
	}

	return ret;
}

// 获取文件名字，没有扩展名字
std::string UtilFileIO::getFileNameNoExt(std::string& fullPath)
{
	int index = fullPath.find_last_of('/');
	std::string ret = "";

	if (index == -1)
	{
		index = fullPath.find_last_of('\\');
	}
	if (index != -1)
	{
		ret = fullPath.substr(index + 1);
	}
	else
	{
		ret = fullPath;
	}

	index = ret.find_last_of('.');
	if (index != -1)
	{
		ret = ret.substr(0, index);
	}

	return ret;
}

// 获取文件路径，没有文件名字
std::string UtilFileIO::getFilePathNoName(std::string& fullPath)
{
	int index = fullPath.find_last_of('/');
	std::string ret = "";

	if (index == -1)
	{
		index = fullPath.find_last_of('\\');
	}
	if (index != -1)
	{
		ret = fullPath.substr(0, index);
	}
	else
	{
		ret = fullPath;
	}

	return ret;
}

std::string UtilFileIO::getFileDir(std::string& fullPath)
{
	return UtilFileIO::getFilePathNoName(fullPath);
}

// 获取文件路径，没有文件名字扩展
std::string UtilFileIO::getFilePathNoExt(std::string& fullPath)
{
	int index = 0;
	std::string ret = fullPath;
	index = fullPath.find_last_of('.');

	if (index != -1)
	{
		ret = fullPath.substr(0, index);
	}

	return ret;
}

// 获取当前文件的父目录名字
std::string UtilFileIO::getFileParentDirName(std::string& fullPath)
{
	std::string parentDir = "";
	int lastSlashIndex = -1;

	// 如果是文件
	if (UtilFileIO::existFile(fullPath))
	{
		lastSlashIndex = fullPath.find_last_of("/");

		if (-1 == lastSlashIndex)
		{
			lastSlashIndex = fullPath.find_last_of("\\");
		}

		if (-1 == lastSlashIndex)
		{
			parentDir = "";
		}
		else
		{
			fullPath = fullPath.substr(0, lastSlashIndex);

			lastSlashIndex = fullPath.find_last_of("/");

			if (-1 == lastSlashIndex)
			{
				lastSlashIndex = fullPath.find_last_of("\\");
			}

			if (-1 == lastSlashIndex)
			{
				parentDir = fullPath;
			}
			else
			{
				parentDir = fullPath.substr(lastSlashIndex + 1, fullPath.length() - (lastSlashIndex + 1));
			}
		}
	}
	else
	{
		lastSlashIndex = fullPath.find_last_of("/");

		if (-1 == lastSlashIndex)
		{
			lastSlashIndex = fullPath.find_last_of("\\");
		}

		if (-1 == lastSlashIndex)
		{
			parentDir = "";
		}
		else
		{
			parentDir = fullPath.substr(lastSlashIndex + 1, fullPath.length() - (lastSlashIndex + 1));
		}
	}

	return parentDir;
}

/**
 * @brief 例如 StreamingAssets 的 Pak 目录为 Project/Content/MyStreamingAssets/aaa/bbb/ccc/MultiOne.pak , 挂载目录就是 Engine/Content/MyStreamingAssets/aaa/bbb/ccc
 */
FString UtilFileIO::convStreamingAssetsPathToMountPath(FString& streamingAssetsPath)
{
	FString ret;
	int contentIndex = -1;
	int lastSlashIndex = -1;

	contentIndex = streamingAssetsPath.Find(UtilEngineWrap::msContent);

	if (-1 != contentIndex)
	{
		ret = streamingAssetsPath.Mid(contentIndex + UtilEngineWrap::msContent.Len(), streamingAssetsPath.Len() - (contentIndex + UtilEngineWrap::msContent.Len()));
	}
	else
	{
		ret = streamingAssetsPath;
	}

	lastSlashIndex = ret.Find(Symbolic::DIR_SEPARATOR);

	if (-1 != lastSlashIndex)
	{
		ret = ret.Mid(0, lastSlashIndex);
	}
	else
	{
		ret = TEXT("");		// 类似 Project/Content/aaa.pak
	}

	return ret;
}

bool UtilFileIO::isBluePrints(FString& filePath)
{
	bool ret = false;

	if (-1 != filePath.Find(UtilEngineWrap::msBlueprints))
	{
		ret = true;
	}

	return ret;
}

MY_END_NAMESPACE