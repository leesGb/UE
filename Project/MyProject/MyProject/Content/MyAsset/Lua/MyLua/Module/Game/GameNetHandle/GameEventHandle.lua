MLoader("MyLua.Libs.Network.CmdDispatch.NetCmdDispatchHandle_KBE");

local M = GlobalNS.Class(GlobalNS.NetCmdDispatchHandle_KBE);
M.clsName = "GameEventHandle";
GlobalNS[M.clsName] = M;

function M:ctor()
end

function M:dtor()
	Ctx.mNetCmdNotify_KBE:removeParamHandle("Client_onHelloCB", self, self.handleTest);
    Ctx.mNetCmdNotify_KBE:removeParamHandle("Client_notifyReliveSeconds", self, self.Client_notifyReliveSeconds);
    Ctx.mNetCmdNotify_KBE:removeParamHandle("handleSendAndGetMessage", self, self.handleSendAndGetMessage);
    Ctx.mNetCmdNotify_KBE:removeParamHandle("notifyTop10RankInfoList", self, self.notifyTop10RankInfoList);
    Ctx.mNetCmdNotify_KBE:removeParamHandle("notifyGameLeftSeconds", self, self.notifyGameLeftSeconds);
    Ctx.mNetCmdNotify_KBE:removeParamHandle("notifyResultRankInfoList", self, self.notifyResultRankInfoList);
    Ctx.mNetCmdNotify_KBE:removeParamHandle("notifyNetworkInvalid", self, self.notifyNetworkInvalid);
    Ctx.mNetCmdNotify_KBE:removeParamHandle("notifySomeMessage", self, self.notifySomeMessage);
    Ctx.mNetCmdNotify_KBE:removeParamHandle("ShowNoticeMsg", self, self.ShowNoticeMsg);
    Ctx.mNetCmdNotify_KBE:removeParamHandle("ShowEmoticon", self, self.ShowEmoticon);
    Ctx.mNetCmdNotify_KBE:removeParamHandle("UpdateMyScore", self, self.UpdateMyScore);
end

function M:init()
	Ctx.mNetCmdNotify_KBE:addParamHandle("Client_onHelloCB", self, self.handleTest);
    Ctx.mNetCmdNotify_KBE:addParamHandle("Client_notifyReliveSeconds", self, self.Client_notifyReliveSeconds);
    Ctx.mNetCmdNotify_KBE:addParamHandle("handleSendAndGetMessage", self, self.handleSendAndGetMessage);
    Ctx.mNetCmdNotify_KBE:addParamHandle("notifyTop10RankInfoList", self, self.notifyTop10RankInfoList);
    Ctx.mNetCmdNotify_KBE:addParamHandle("notifyGameLeftSeconds", self, self.notifyGameLeftSeconds);
    Ctx.mNetCmdNotify_KBE:addParamHandle("notifyResultRankInfoList", self, self.notifyResultRankInfoList);
    Ctx.mNetCmdNotify_KBE:addParamHandle("notifyNetworkInvalid", self, self.notifyNetworkInvalid);
    Ctx.mNetCmdNotify_KBE:addParamHandle("notifySomeMessage", self, self.notifySomeMessage);
    Ctx.mNetCmdNotify_KBE:addParamHandle("ShowNoticeMsg", self, self.ShowNoticeMsg);
    Ctx.mNetCmdNotify_KBE:addParamHandle("ShowEmoticon", self, self.ShowEmoticon);
    Ctx.mNetCmdNotify_KBE:addParamHandle("UpdateMyScore", self, self.UpdateMyScore);
end

function M:dtor()
    
end

function M:handleTest(cmd)
    
end

function M:handleSendAndGetMessage(params)
    local msgName = params[0];
    if not self:filterMessage(msgName) then
        if Ctx.mUiMgr:hasForm(GlobalNS.UiFormId.eUiConsoleDlg) then
        local form = Ctx.mUiMgr:getForm(GlobalNS.UiFormId.eUiConsoleDlg);
            if nil ~= form and form.mIsReady then
                form:onSetLogText(msgName);
            end
        end
    end    
end

function M:filterMessage(msgname) --消息过滤
    if string.find(msgname, "Client_onUpdateBasePosXZ") ~= nil or
       string.find(msgname, "Baseapp_onUpdateDataFromClient") ~= nil or
       string.find(msgname, "Client_onUpdateData_xyz") ~= nil or
       string.find(msgname, "Baseapp_onClientActiveTick") ~= nil or
       string.find(msgname, "Client_onAppActiveTickCB") ~= nil or
       string.find(msgname, "Client_onEntityEnterWorld") ~= nil or
       string.find(msgname, "Client_onUpdatePropertys") ~= nil or
       string.find(msgname, "Client_setSpaceData") ~= nil or
       string.find(msgname, "Client_onEntityLeaveWorldOptimized") ~= nil or
       string.find(msgname, "Client_onRemoteMethodCall") ~= nil or
       string.find(msgname, "Client_onUpdateData_xz") ~= nil
    then
        return true;
    else
        return false;
    end
end

function M:Client_notifyReliveSeconds(params)
    local reliveTime = params[0]; --param是C#的数组，从0开始
    local enemyName = params[1];
    local isKilledBySelf = params[2];

    --重生后停止移动
    GlobalNS.CSSystem.Ctx.msInstance.mDataPlayer.mDataHero:setMoveVec(Vector2.New(0, 0));

    CtxExt.mPlayerData.mGameData.reliveTime = reliveTime;
    CtxExt.mPlayerData.mGameData.enemyName = enemyName;
    CtxExt.mPlayerData.mGameData.iskilledbyself = isKilledBySelf;
    Ctx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiRelivePanel);
end

function M:notifyTop10RankInfoList(params)
    CtxExt.mPlayerData.mGameData:setTop10RankList(params);
end

function M:notifyGameLeftSeconds(params)
    local leftseconds = params[0];
    CtxExt.mPlayerData.mGameData:setGameTime(leftseconds);
end

function M:notifyResultRankInfoList(params)
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiPlayerDataPanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiOptionPanel);
    Ctx.mUiMgr:exitForm(GlobalNS.UiFormId.eUiTopXRankPanel);

    Ctx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiRankListPanel);
    CtxExt.mPlayerData.mGameData:setRankInfoList(params);
    CtxExt.mPlayerData.mGameData:clearResource();
end

function M:notifyNetworkInvalid()
    CtxExt.mPlayerData.mGameData.mMessageMethond = 1;
    CtxExt.mPlayerData.mGameData:ShowMessageBox("已与服务器断开连接");
end

function M:notifySomeMessage(params)
    local msg = params[0];
    CtxExt.mPlayerData.mGameData:ShowRollMessage(msg);
end

function M:ShowNoticeMsg()
    local times = 0;
    if GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:hasKey("NoticeTimes") then
        times = GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:getInt("NoticeTimes");
    end
    
    if GlobalNS.CSSystem.Ctx.msInstance.mShareData.noticeTimes > times then
        GlobalNS.CSSystem.Ctx.msInstance.mSystemSetting:setInt("NoticeTimes", times+1);
        
        local msg = string.gsub(GlobalNS.CSSystem.Ctx.msInstance.mShareData.noticeMsg, "\\n", "\n");
        CtxExt.mPlayerData.mGameData:ShowMessageBox(msg);
    end
end

function M:ShowEmoticon()
    -- 结算时就不显示了
    local form = Ctx.mUiMgr:getForm(GlobalNS.UiFormId.eUiRankListPanel);
    if nil == form or not form:isVisible() then            
         Ctx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiEmoticonPanel);
    end
end

function M:UpdateMyScore(params)
    local score = params[0];
    local form = Ctx.mUiMgr:getForm(GlobalNS.UiFormId.eUiPlayerDataPanel);
    if nil ~= form and form:isVisible() then
        form:refreshScore(score);
    else
        CtxExt.mPlayerData.mGameData.mMyScore = score;
    end
end

return M;