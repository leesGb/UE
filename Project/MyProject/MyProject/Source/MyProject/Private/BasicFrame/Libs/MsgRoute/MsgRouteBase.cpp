﻿#include "MyProject.h"
#include "MsgRouteBase.h"

MsgRouteBase::MsgRouteBase()
{

}

MsgRouteBase::~ThreadLogMR()
{

}

MsgRouteBase::MsgRouteBase(MsgRouteId id)
{
	this->mMsgType = MsgRouteType::eMRT_BASIC;
	this->mMsgId = id;
}

void MsgRouteBase::resetDefault()
{

}