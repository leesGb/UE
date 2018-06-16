﻿#include "MyProject.h"
#include "PlayerAttack.h"
#include "BeingEntity.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerAttack, BeingEntityAttack)

PlayerAttack::PlayerAttack(BeingEntity* entity)
{
	Super(entity);
}

MY_END_NAMESPACE