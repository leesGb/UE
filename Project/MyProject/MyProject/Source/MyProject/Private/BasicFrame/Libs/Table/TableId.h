﻿#ifndef __TableId_H
#define __TableId_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class TableId
{
	TABLE_OBJECT,           // 道具基本表
	TABLE_CARD,             // 卡牌基本表
	TABLE_SKILL,            // 技能基本表// 添加一个表的步骤二

	eTableTotal             // 表的总数
};

MY_END_NAMESPACE

#endif