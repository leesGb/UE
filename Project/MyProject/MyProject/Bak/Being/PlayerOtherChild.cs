﻿namespace SDK.Lib
{
    public class PlayerOtherChild : PlayerChild
    {
        public PlayerOtherChild()
        {
            this.mTypeId = "PlayerOtherChild";
            this.mEntityType = EntityType.ePlayerOtherChild;
            this.mMovement = new PlayerOtherChildMovement(this);
            this.mAttack = new PlayerOtherChildAttack(this);
            this.mEntityUniqueId = Ctx.msInstance.mPlayerMgr.genChildNewStrId();
        }

        override public void initRender()
        {
            if (!this.isPrefabPathValid())
            {
                this.setPrefabPath("World/Model/PlayerOther.prefab");
            }

            if (null == this.mRender)
            {
                this.mRender = new PlayerOtherChildRender(this);
            }

            this.mRender.init();
        }
    }
}