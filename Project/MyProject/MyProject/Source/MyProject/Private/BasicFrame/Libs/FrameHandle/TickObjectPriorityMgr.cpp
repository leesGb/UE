﻿#include "MyProject.h"
#include "TickObjectPriorityMgr.h"
#include "MClassFactory.h"
#include "MacroDef.h"
#include "Ctx.h"
#include "LogSys.h"
#include "LogTypeId.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(TickObjectPriorityMgr, DelayPriorityHandleMgr)

TickObjectPriorityMgr::TickObjectPriorityMgr()
{

}

void TickObjectPriorityMgr::init()
{
	Super::init();
}

void TickObjectPriorityMgr::dispose()
{
	Super::dispose();
}

void TickObjectPriorityMgr::setClientDispose(bool isDispose)
{

}

bool TickObjectPriorityMgr::isClientDispose()
{
	return false;
}

void TickObjectPriorityMgr::onTick(float delta, TickMode tickMode)
{
	this->advance(delta, tickMode);
}

void TickObjectPriorityMgr::advance(float delta, TickMode tickMode)
{
	this->_incDepth();

	this->_onPreAdvance(delta, tickMode);
	this->_onExecAdvance(delta, tickMode);
	this->_onPostAdvance(delta, tickMode);

	this->_decDepth();
}

void TickObjectPriorityMgr::_onPreAdvance(float delta, TickMode tickMode)
{

}

void TickObjectPriorityMgr::_onExecAdvance(float delta, TickMode tickMode)
{
	int idx = 0;
	int count = this->mNoOrPriorityList.count();
	ITickedObject* tickObject = nullptr;

	while (idx < count)
	{
		tickObject = (ITickedObject*)this->mNoOrPriorityList.get(idx);

		if (nullptr != (IDelayHandleItem*)tickObject)
		{
			if (!(IDelayHandleItem*)tickObject)->isClientDispose())
			{
				tickObject->onTick(delta, tickMode);
			}
		}
		else
		{
			if (MacroDef.ENABLE_LOG)
			{
				GLogSys->log("TickObjectPriorityMgr::_onExecAdvance, failed", LogTypeId::eLogCommon);
			}
		}

		++idx;
	}
}

void TickObjectPriorityMgr::_onPostAdvance(float delta, TickMode tickMode)
{

}

MY_END_NAMESPACE