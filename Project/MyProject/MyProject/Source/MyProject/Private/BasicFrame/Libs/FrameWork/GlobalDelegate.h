﻿#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class PromiseEventDispatch;

/**
* @brief 全局性的事件
*/
class GlobalDelegate : public GObject
{
public:
	PromiseEventDispatch* mCoreInitedEventDispatch;	// Core 初始化完成

public:
	GlobalDelegate();

	void init();
	void dispose();
};

MY_END_NAMESPACE