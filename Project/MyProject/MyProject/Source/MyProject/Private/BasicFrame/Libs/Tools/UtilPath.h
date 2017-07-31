#ifndef __UtilPath_H
#define __UtilPath_H

#include <string>
#include <sstream>
#include "Containers/UnrealString.h"
#include "IPlatformFileSandboxWrapper.h"	// FSandboxPlatformFile

class UtilPath
{
public:
	// ���·����������Ŀ¼��Ŀǰֻ֧����������Ҫ�ļ�������
	template<class T0, class T1>
	static std::string Combine(T0 param0, T1 param1);

	// https://wiki.unrealengine.com/Packaged_Game_Paths,_Obtain_Directories_Based_on_Executable_Location
	static FString BaseDir();
	static FString RootDir();
	static FString GameDir();
	static FString GameContentDir();

	static FString GameSavedDir();
	static FString GameLogDir();

	static FString GetFilenameOnDisk(FString FullFilename);
	static FString ConvertToSandboxPath(FString FullFilename);

	static FString FPaths_ConvertToSandboxPath(FString FullFilename);
	static void NormalizeDirectoryName(FString& InPath);

	static bool FileExists(const std::string& InPath);
};

// ģ��ʵ��
#include "UtilPath.inl"

//template<class T0, class T1>
//static std::string UtilPath::Combine(T0 param0, T1 param1)
//{
//	std::stringstream strStream;
//	strStream << param0 << "/" << "param1";
//
//	return strStream.str();
//}

#endif