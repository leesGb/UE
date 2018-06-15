﻿#pragma once

#include "BeingEntityMovement.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

class PlayerMovement : public BeingEntityMovement
{
public:
	PlayerMovement(SceneEntityBase* entity)
		: base(entity)
	{

	}
};

MY_END_NAMESPACE