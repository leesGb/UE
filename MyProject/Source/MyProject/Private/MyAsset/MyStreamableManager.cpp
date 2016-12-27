#include "MyProject.h"
#include "Misc/StringAssetReference.h"	// FStringAssetReference
#include "UtilStr.h"
#include <string>
#include "MyStreamableManager.h"

FMyStreamableManager::FMyStreamableManager()
{
	
}

FMyStreamableManager::~FMyStreamableManager()
{
	
}

void FMyStreamableManager::init()
{

}

void FMyStreamableManager::dispose()
{

}

//UObject* FMyStreamableManager::GetStreamed(std::string const& InTargetName)
//{
//	FStringAssetReference assetRef;
//	assetRef.SetPath(UtilStr::ConvStdStr2FString(const_cast<std::string&>(InTargetName)));
//  StreamableManager::GetStreamed 私有函数，不能调用
//	return mStreamableManager.GetStreamed(assetRef);
//}

UObject* FMyStreamableManager::SynchronousLoad(std::string& path)
{
	FStringAssetReference assetRef;
	assetRef.SetPath(UtilStr::ConvStdStr2FString(path));
	return mStreamableManager.SynchronousLoad(assetRef);
}

void FMyStreamableManager::RequestAsyncLoad(const std::string& TargetToStream, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority)
{
	FStringAssetReference assetRef;
	assetRef.SetPath(UtilStr::ConvStdStr2FString(const_cast<std::string&>(TargetToStream)));
	mStreamableManager.RequestAsyncLoad(assetRef, DelegateToCall, Priority);
}

void FMyStreamableManager::RequestAsyncLoad(const FStringAssetReference& TargetToStream, FStreamableDelegate DelegateToCall, TAsyncLoadPriority Priority)
{
	mStreamableManager.RequestAsyncLoad(TargetToStream, DelegateToCall, Priority);
}