﻿#include "MyProject.h"
#include "NetModuleDispatchHandle.h"
#include "MByteBuffer.h"
#include "Prequisites.h"
#include "UtilStr.h"
#include "NetCmdDispatchHandle.h"
#include "AddOnceEventDispatch.h"
#include "NetCmdDispatchInfo.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "MClassFactory.h"
#include "UtilConvert.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(NetModuleDispatchHandle, GObject)

NetModuleDispatchHandle::NetModuleDispatchHandle()
{
	
}

NetModuleDispatchHandle::~NetModuleDispatchHandle()
{
	
}

void NetModuleDispatchHandle::init()
{

}

void NetModuleDispatchHandle::dispose()
{

}

void NetModuleDispatchHandle::addCmdHandle(uint8 cmdId, EventDispatchDelegate handle)
{
	if (!this->mId2DispatchDic.containsKey(cmdId))
	{
		this->mId2DispatchDic[cmdId] = MY_NEW AddOnceEventDispatch();
	}

	this->mId2DispatchDic[cmdId]->addEventHandle(handle);
}

void NetModuleDispatchHandle::removeCmdHandle(uint8 cmdId, EventDispatchDelegate handle)
{
	if (this->mId2DispatchDic.containsKey(cmdId))
	{
		this->mId2DispatchDic[cmdId]->removeEventHandle(handle);
	}
	else
	{
		// 日志
	}
}

void NetModuleDispatchHandle::handleMsg(NetCmdDispatchInfo* cmdDispInfo)
{
	if (this->mId2DispatchDic.containsKey(cmdDispInfo->byCmd))
    {
		GLogSys->log(
			UtilStr::Format(
				"Handle Msg: byCmd = {0},  byParam = {1}", 
				UtilConvert::convInt2Str(cmdDispInfo->byCmd),
				UtilConvert::convInt2Str(cmdDispInfo->byParam)
			)
		);
		this->mId2DispatchDic.value(cmdDispInfo->byCmd)->dispatchEvent(cmdDispInfo);
    }
    else
    {
		GLogSys->log(
			UtilStr::Format(
				"Handle Msg: byCmd = {0},  byParam = {1}", 
				UtilConvert::convInt2Str(cmdDispInfo->byCmd),
				UtilConvert::convInt2Str(cmdDispInfo->byParam)
			)
		);
    }

    //if(mLuaCSBridgeNetDispHandle != nullptr)
    //{
    //    mLuaCSBridgeNetDispHandle.handleMsg(msg, byCmd, byParam);
    //}
}

MY_END_NAMESPACE