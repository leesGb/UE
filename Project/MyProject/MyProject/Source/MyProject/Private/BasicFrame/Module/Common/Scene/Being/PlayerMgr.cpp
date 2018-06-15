#include "MyProject.h"
#include "PlayerMgr.h"
#include "PlayerMain.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerMgr::PlayerMgr()
{
	this.mCurNum = 0;
	this.mMaxNum = 10;
}

void PlayerMgr::_onTickExec(float delta, TickMode tickMode)
{
	if (TickMode.eTM_Update == tickMode)
	{
		int idx = 0;
		int count = this.mSceneEntityList.count();
		SceneEntityBase entity = null;

		while (idx < count)
		{
			entity = this.mSceneEntityList[idx];

			if (Ctx.msInstance.mConfig.mIsActorMoveUseFixUpdate)
			{
				if (EntityType.ePlayerMain != entity.getEntityType())
				{
					if (!entity.isClientDispose())
					{
						entity.onTick(delta, tickMode);
					}
				}
			}
			else
			{
				if (!entity.isClientDispose())
				{
					entity.onTick(delta, tickMode);
				}
			}

			++idx;
		}
	}
	else if(TickMode.eTM_LateUpdate == tickMode)
	{
		this.postUpdate();
	}
}

void PlayerMgr::postUpdate()
{
   
}

PlayerMain* PlayerMgr::createHero()
{
	return new PlayerMain();
}

void PlayerMgr::addHero(PlayerMain* hero)
{
	if (null != hero)
	{
		this.mHero = hero as PlayerMain;
		this.addPlayer(this.mHero);

		if (Ctx.msInstance.mConfig.mIsActorMoveUseFixUpdate)
		{
			Ctx.msInstance.mFixedTickMgr.addTick(this.mHero as ITickedObject);
		}
	}
}

void PlayerMgr::removeHero()
{
	if (null != this.mHero)
	{
		if (Ctx.msInstance.mConfig.mIsActorMoveUseFixUpdate && null != Ctx.msInstance.mFixedTickMgr)
		{
			Ctx.msInstance.mFixedTickMgr.removeTick(this.mHero as ITickedObject);
		}

		this.removePlayer(this.mHero);
		this.mHero = null;
	}
}

PlayerMain* PlayerMgr::getHero()
{
	return this.mHero;
}

void PlayerMgr::init()
{
	base.init();
}

void PlayerMgr::addPlayer(Player* player)
{
	this.addEntity(player);
}

void PlayerMgr::removePlayer(Player* player)
{
	this.removeEntity(player);
	--this.mMaxNum;
}

void PlayerMgr::createPlayerMain()
{
	this.mHero = new PlayerMain();
	this.mHero.init();
	this.mHero.setDestPos(new UnityEngine.Vector3(50, 1.3f, 50f), true);
	this.mHero.setDestRotateEulerAngle(UtilMath.UnitQuat.eulerAngles, true);
}

MY_END_NAMESPACE