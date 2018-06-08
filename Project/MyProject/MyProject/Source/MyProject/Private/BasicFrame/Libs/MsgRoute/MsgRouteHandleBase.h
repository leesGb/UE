﻿#ifndef __MsgRouteHandleBase_H
#define __MsgRouteHandleBase_H

#include "MDictionary.h"
#include "MsgRouteId.h"
#include "EventDispatchDelegate.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceEventDispatch;

class MsgRouteHandleBase : public GObject
{
	M_DECLARE_CLASS(MsgRouteHandleBase, GObject)

public:
	MDictionary<int, AddOnceEventDispatch*> mId2HandleDic;

public:
	MsgRouteHandleBase();
	// warning C4265: 'MsgRouteHandleBase': class has virtual functions, but destructor is not virtual
	virtual ~MsgRouteHandleBase();

	virtual void init();
	virtual void dispose();

	void addMsgRouteHandle(MsgRouteId msgRouteId, EventDispatchDelegate handle);
	void removeMsgRouteHandle(MsgRouteId msgRouteId, EventDispatchDelegate handle);
	virtual void handleMsg(IDispatchObject* dispObj, uint uniqueId);
};

MY_END_NAMESPACE

#endif