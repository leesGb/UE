﻿#include "MyProject.h"
#include "ResItem.h"
#include "EngineApi.h"
#include "Common.h"
#include "ClassAssetInsRes.h"

ClassAssetInsRes::ClassAssetInsRes()
{

}

void ClassAssetInsRes::initImpl(ResItem* res)
{
	//mGo = res.getObject(res.getPrefabName()) as GameObject;
	//base.initImpl(res);
}

UObject* ClassAssetInsRes::InstantiateObject(std::string resName)
{
	mRetGO = nullptr;

	if (nullptr == mGo)
	{
		GLogSys->log("prefab 为 null");
	}
	else
	{
		// mRetGO = GameObject.Instantiate(mGo) as GameObject;
		if (nullptr == mRetGO)
		{
			GLogSys->log("不能实例化数据");
		}
	}
	return mRetGO;
}

UClass* ClassAssetInsRes::getObject()
{
	return mGo;
}

void ClassAssetInsRes::unload()
{
	if (mGo != nullptr)
	{
		//UtilApi.UnloadAsset(mGo);      // 强制卸载资源数据
		//UtilApi.DestroyImmediate(mGo, true);
		EngineApi::UnloadUnusedAssets();
		mGo = nullptr;
	}
	mRetGO = nullptr;
	InsResBase::unload();
}