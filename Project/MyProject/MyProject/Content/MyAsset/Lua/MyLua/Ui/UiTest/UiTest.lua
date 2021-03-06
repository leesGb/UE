MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiTest.TestNS");
MLoader("MyLua.Ui.UiTest.TestData");
MLoader("MyLua.Ui.UiTest.TestCV");

local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiTest";
GlobalNS.TestNS[M.clsName] = M;

function M:ctor()
    --print("M:ctor()");
    --print(tostring(self));
	self.mId = GlobalNS.UiFormId.eUiTest;
	self.mData = GlobalNS.new(GlobalNS.TestNS.TestData);
end

function M:dtor()
	
end

function M:onInit()
    M.super.onInit(self);
    --print("M:onInit()");
	
	self.mTestBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mTestBtn:addEventHandle(self, self.onBtnClk, 0);
end

function M:onReady()
    -- TODO: 之前使用的是 self.super ，结果如果子类中没有实现这个函数，然后这个函数又被调用了，结果直接调用父类的，而父类中有会再次调用 self 的 super 的函数，结果就死循环了，不断的调用自己
    -- self.super.onReady(self)
    M.super.onReady(self);
    --print("M:onReady()");
    --GlobalNS.CSImportToLua.UtilEngineWrap.addEventHandle(self.gameObject, self.onBtnClk, 0);
	--SDK.Lib.UtilEngineWrap.addEventHandle(self.gameObject, "Button", self.onBtnClk);
	--GlobalNS.UtilEngineWrap.addEventHandleByPath(self.mGuiWin, GlobalNS.TestNS.TestPath.BtnTest, self, self.onBtnClk);
	self.mTestBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, GlobalNS.TestNS.TestPath.BtnTest));
end

function M:onShow()
    M.super.onShow(self);
    --print("M:onShow()");
    
    --local aaa = 0;
    --aaa.print();
    
    --error("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
end

function M:onHide()
    M.super.onHide(self);
    --print("M:onHide()");
end

function M:onExit()
    M.super.onExit(self);
    --print("M:onExit()");
end

function M:onBtnClk()
	--self:testSendMsg();
	--self:testLoginMsg();
	--self:testEmptyLoginMsg();
	self:testEnumLoginMsg();
end

function M:testSendMsg()
	local msg = {};
	msg.requid = 1000;
	msg.reqguid = 1000;
	msg.reqaccount = "aaaaa";
	GlobalNS.UtilMsg.sendMsg(1000, msg);
end

function M:testLoginMsg()
	local rpc = {};
	rpc.request = {};
	rpc.request.id = 1002;
	rpc.request.service = "rpc.Login";
	rpc.request.method = "Login";
	
    local msg = {};
    msg.account = "account";
    msg.password = "password";
    GlobalNS.UtilMsg.sendMsgRpc(1002, rpc, msg);
end

function M:testEmptyLoginMsg()
	local rpc = {};
	rpc.request = {};
	rpc.request.id = 1002;
	rpc.request.service = "rpc.Login";
	rpc.request.method = "Login";
	
    local msg = {};
    GlobalNS.UtilMsg.sendMsgRpc(1002, rpc, msg);
end

function M:testEnumLoginMsg()
	local rpc = {};
	rpc.request = {};
	rpc.request.id = 1002;
	rpc.request.service = "rpc.Login";
	rpc.request.method = "Login";
	
    local msg = {};
    msg.result = "ERR_SERVER_FULL";
	--msg.result = 2;
    msg.error_str = "password";
    GlobalNS.UtilMsg.sendMsgRpc(1003, rpc, msg);
end

return M;

