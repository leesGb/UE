﻿#ifndef __NetModuleDispatchHandle_H
#define __NetModuleDispatchHandle_H

#include "MDictionary.h"
#include "Platform.h"		// uint8
#include "EventDispatchDelegate.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class NetCmdDispatchHandle;
class MByteBuffer;
class AddOnceEventDispatch;
class NetCmdDispatchInfo;

class NetModuleDispatchHandle : public GObject
{
	M_DECLARE_CLASS(NetModuleDispatchHandle, GObject)

public:
	MDictionary<uint8, AddOnceEventDispatch*> mId2DispatchDic;
    //LuaCSBridgeNetDispHandle mLuaCSBridgeNetDispHandle;     // Lua 网络事件处理器

public:
	NetModuleDispatchHandle();
	virtual ~NetModuleDispatchHandle();

	virtual void init();
	virtual void dispose();

	void addCmdHandle(uint8 cmdId, EventDispatchDelegate handle);
	void removeCmdHandle(uint8 cmdId, EventDispatchDelegate handle);

	virtual void handleMsg(NetCmdDispatchInfo* cmdDispInfo);
};

MY_END_NAMESPACE

#endif