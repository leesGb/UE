#ifndef __UiFormId_H
#define __UiFormId_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class UiFormId
{
	eUiPack,		// 背包
	eUiLog,			// 日志
	eUiTestCanvas,	// 测试 Canvas
	eUiTestUMG,		// 测试 UMG
	eUiFunctionBar,	// 底下功能栏
	eUiAppDownload,
	eUiTotal
};

MY_END_NAMESPACE

#endif				// __UiFormId_H