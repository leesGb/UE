MLoader("MyLua.Module.Common.Module.ILoginSys");
MLoader("MyLua.Module.Game.EventCB.GameNetHandleCB");

local M = GlobalNS.Class(GlobalNS.IGameSys);
M.clsName = "GameSys";
GlobalNS[M.clsName] = M;

function M:ctor()
	self.mGameNetHandleCB_KBE = GlobalNS.new(GlobalNS.GameNetHandleCB_KBE);
end

function M:dtor()

end

function M:init()
    local gameNetHandleCB = GlobalNS.new(GlobalNS.GameNetHandleCB);
    Ctx.mNetCmdNotify:addOneDispatch(gameNetHandleCB);    -- 设置网络模块处理

	self.mGameNetHandleCB_KBE:init();
end

return M;