﻿#include "MyProject.h"
#include "FrameTimerItem.h"
#include "EventDispatchFunctionObject.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

FrameTimerItem::FrameTimerItem()
{
	this->mInternal = 1;
	this->mTotalFrameCount = 1;
	this->mCurFrame = 0;
	this->mCurLeftFrame = 0;
	this->mIsInfineLoop = false;
	this->mTimerDispatch = nullptr;
	this->mIsDisposed = false;
}

FrameTimerItem::~FrameTimerItem()
{

}

void FrameTimerItem::init()
{

}

void FrameTimerItem::dispose()
{

}

void FrameTimerItem::addTimerEventHandle(EventDispatchDelegate handle)
{
	if (nullptr == this->mTimerDispatch)
	{
		this->mTimerDispatch = MY_NEW EventDispatchFunctionObject();
	}

	this->mTimerDispatch->setFuncObject(handle);
}

void FrameTimerItem::removeTimerEventHandle(EventDispatchDelegate handle)
{
	this->mTimerDispatch->clearFuncObject();
}

void FrameTimerItem::onFrameTimer()
{
	if (this->mIsDisposed)
	{
		return;
	}

	++this->mCurFrame;
	++this->mCurLeftFrame;

	if (this->mIsInfineLoop)
	{
		if (this->mCurLeftFrame == mInternal)
		{
			this->mCurLeftFrame = 0;

			this->mTimerDispatch->call(this);
		}
	}
	else
	{
		if (this->mCurFrame == this->mTotalFrameCount)
		{
			this->mIsDisposed = true;

			this->mTimerDispatch->call(this);
		}
		else
		{
			if (this->mCurLeftFrame == this->mInternal)
			{
				this->mCurLeftFrame = 0;

				this->mTimerDispatch->call(this);
			}
		}
	}
}

void FrameTimerItem::reset()
{
	this->mCurFrame = 0;
	this->mCurLeftFrame = 0;
	this->mIsDisposed = false;
}

MY_END_NAMESPACE