﻿#pragma once

#include "AuxMObjectLoaderBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "ResPackType.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 预制
 */
class AuxMClassLoader : public AuxMObjectLoaderBase
{
	M_DECLARE_CLASS(AuxMClassLoader, AuxMObjectLoaderBase)

public:
	AuxMClassLoader();
};

MY_END_NAMESPACE