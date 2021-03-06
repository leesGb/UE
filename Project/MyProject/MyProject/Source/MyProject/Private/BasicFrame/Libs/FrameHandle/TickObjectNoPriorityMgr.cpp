﻿#include "MyProject.h"
#include "TickObjectNoPriorityMgr.h"
#include "MClassFactory.h"
#include "MacroDef.h"
#include "Ctx.h"
#include "LogSys.h"
#include "LogTypeId.h"
#include "INoOrPriorityList.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(TickObjectNoPriorityMgr, DelayNoPriorityHandleMgr)

TickObjectNoPriorityMgr::TickObjectNoPriorityMgr()
{

}

void TickObjectNoPriorityMgr::init()
{
	Super::init();
}

void TickObjectNoPriorityMgr::dispose()
{
	Super::dispose();
}

void TickObjectNoPriorityMgr::onTick(float delta, TickMode tickMode)
{
	this->_incDepth();

	this->_onPreAdvance(delta, tickMode);
	this->_onExecAdvance(delta, tickMode);
	this->_onPostAdvance(delta, tickMode);

	this->_decDepth();
}

void TickObjectNoPriorityMgr::_onPreAdvance(float delta, TickMode tickMode)
{

}

void TickObjectNoPriorityMgr::_onExecAdvance(float delta, TickMode tickMode)
{
	int index = 0;
	int count = this->mNoOrPriorityList->count();
	ITickedObject* tickObject = nullptr;

	while (index < count)
	{
		tickObject = (ITickedObject*)this->mNoOrPriorityList->get(index);

		if (nullptr != (IDelayHandleItem*)tickObject)
		{
			//if (!((IDelayHandleItem*)tickObject)->isClientDispose())
			if (!((GObject*)tickObject)->isClientDispose())
			{
				((GObject*)tickObject)->onTick(delta, tickMode);
			}
		}
		else
		{
			if (MacroDef::ENABLE_LOG)
			{
				GLogSys->log("TickObjectNoPriorityMgr::_onExecAdvance, failed", LogTypeId::eLogCommon);
			}
		}

		++index;
	}
}

void TickObjectNoPriorityMgr::_onPostAdvance(float delta, TickMode tickMode)
{

}

MY_END_NAMESPACE