MLoader("MyLua.Libs.Network.CmdDispatch.NetCmdDispatchHandle");

local M = GlobalNS.Class(GlobalNS.NetCmdDispatchHandle);
M.clsName = "GameTestCmdHandle";
GlobalNS[M.clsName] = M;

function M:ctor()
    self:addParamHandle(MSG_ReqTest, self, self.handleTest);
	self:addParamHandle(LoginResponse, self, self.LoginResponse);
end

function M:dtor()
    
end

function M:handleTest(cmd)
    --GlobalNS.CSSystem.onTestProtoBuf(cmd);
end

function M:handleLoginResponse(cmd)
	Ctx.mLogSys:log(cmd.result, GlobalNS.LogTypeId.eLogCommon);
end

return M;