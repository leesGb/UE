﻿#include "MyProject.h"
#include "Common.h"
#include "UObject/Class.h"	// UClass
#include "NonRefCountResLoadResultNotify.h"		// NonRefCountResLoadResultNotify
#include "ClassAssetLoadItem.h"

ClassAssetLoadItem::ClassAssetLoadItem()
{
	this->mResObj = nullptr;
}

UObject* ClassAssetLoadItem::getObject()
{
	return this->mResObj;
}

void ClassAssetLoadItem::setObject(UObject* value)
{
	this->mResObj = Cast<UClass>(value);
}

void ClassAssetLoadItem::syncLoad()
{
	this->mResObj = GMyStreamableManager->SynchronousLoadType<UClass>(this->mPath);

	if (nullptr != mResObj)
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
	}
	else
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setFailed();
	}

	this->mNonRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void ClassAssetLoadItem::asyncLoad()
{
	mAssetRef.SetPath(UtilStr::ConvStdStr2FString(const_cast<std::string&>(this->mPath)));

	GMyStreamableManager->RequestAsyncLoad(mAssetRef, FStreamableDelegate::CreateRaw(this, &ClassAssetLoadItem::onAsyncLoaded));
}

void ClassAssetLoadItem::onAsyncLoaded()
{
	//this->mResObj = Cast<UClass>GMyStreamableManager->GetStreamed(this->mPath);
	this->mResObj = Cast<UClass>(mAssetRef.ResolveObject());

	if (nullptr != mResObj)
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
	}
	else
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setFailed();
	}

	this->mNonRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void ClassAssetLoadItem::load()
{
	LoadItem::load();

	if (!this->getLoadNeedCoroutine())
	{
		this->syncLoad();
	}
	else
	{
		this->asyncLoad();
	}
}

void ClassAssetLoadItem::unload()
{
	LoadItem::unload();
}