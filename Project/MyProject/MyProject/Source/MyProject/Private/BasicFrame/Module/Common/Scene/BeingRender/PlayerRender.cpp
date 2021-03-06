﻿#include "MyProject.h"
#include "PlayerRender.h"
#include "SceneEntityBase.h"
#include "SceneEntityRenderBase.h"
#include "TickMode.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerRender, BeingEntityRender)

PlayerRender::PlayerRender(SceneEntityBase* entity_)
	: Super(entity_)
{
	
}

void PlayerRender::_onSelfChanged()
{
	Super::_onSelfChanged();
}

/**
 * @brief 释放基本数据
 */
void PlayerRender::dispose()
{
	Super::dispose();
}

void PlayerRender::attachToParentNode(SceneEntityRenderBase* render)
{
	//if(this->isSelfValid() && render.isSelfValid())
	//{
	//	UtilEngineWrap::SetParent(render.getSelfActor(), this->mSelfActor, false);
	//}
}

void PlayerRender::onTick(float delta, TickMode tickMode)
{
	Super::onTick(delta, tickMode);
}

MY_END_NAMESPACE