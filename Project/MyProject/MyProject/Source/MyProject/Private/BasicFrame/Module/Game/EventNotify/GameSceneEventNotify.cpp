﻿#include "MyProject.h"
#include "GameSceneEventNotify.h"
#include "Prequisites.h"
#include "UiFunctionBar.h"
#include "UiFormId.h"

#ifdef ENABLE_UNIT_TEST
	#include "TestMain.h"
#endif

MY_BEGIN_NAMESPACE(MyNS)

GameSceneEventNotify::GameSceneEventNotify()
{
	
}

GameSceneEventNotify::~GameSceneEventNotify()
{
	
}

void GameSceneEventNotify::init()
{

}

void GameSceneEventNotify::dispose()
{
#ifdef ENABLE_UNIT_TEST
	if (!this->mTestMain.isNull())
	{
		this->mTestMain->dispose();
		this->mTestMain.setNull();
	}
#endif
}

// 场景加载完成处理事件
void GameSceneEventNotify::onLevelLoaded()
{
	GUiMgr->loadAndShow<UUiFunctionBar>(UiFormId::eUiFunctionBar);

	this->runTest();
}

void GameSceneEventNotify::runTest()
{
#ifdef ENABLE_UNIT_TEST
	this->mTestMain = MySharedPtr<TestMain>(MY_NEW TestMain());
	this->mTestMain->runTest();
#endif
}

MY_END_NAMESPACE