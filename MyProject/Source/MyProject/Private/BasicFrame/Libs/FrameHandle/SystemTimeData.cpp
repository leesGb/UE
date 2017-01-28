﻿#include "MyProject.h"
#include "SystemTimeData.h"
#include "EngineApi.h"

SystemTimeData::SystemTimeData()
{
	this->mPreTime = 0;
	this->mCurTime = 0;
	this->mDeltaSec = 0.0f;
}

void SystemTimeData::init()
{

}

void SystemTimeData::dispose()
{

}

float SystemTimeData::getDeltaSec()
{
	return this->mDeltaSec;
}

void SystemTimeData::setDeltaSec(float value)
{
	this->mDeltaSec = value;
}

long SystemTimeData::getCurTime()
{
	return this->mCurTime;
}
void SystemTimeData::setCurTime(long value)
{
	this->mCurTime = value;
}

void SystemTimeData::nextFrame()
{
	this->mCurTime = EngineApi::getUTCSec();

	if (this->mPreTime != 0.0f)     // 第一帧跳过，因为这一帧不好计算间隔
	{
		this->mDeltaSec = this->mCurTime - this->mPreTime;
	}
	else
	{
		this->mDeltaSec = 1 / 24;        // 每秒 24 帧
	}

	this->mPreTime = this->mCurTime;
}