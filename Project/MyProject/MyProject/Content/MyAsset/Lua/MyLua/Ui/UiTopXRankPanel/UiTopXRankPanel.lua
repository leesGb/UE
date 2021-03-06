MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Ui.Base.Form");

MLoader("MyLua.Libs.Auxiliary.AuxUIComponent.AuxButton");

MLoader("MyLua.Ui.UiTopXRankPanel.TopXRankPanelNS");
MLoader("MyLua.Ui.UiTopXRankPanel.TopXRankPanelData");
MLoader("MyLua.Ui.UiTopXRankPanel.TopXRankPanelCV");

--UI区
local M = GlobalNS.Class(GlobalNS.Form);
M.clsName = "UiTopXRankPanel";
GlobalNS.TopXRankPanelNS[M.clsName] = M;

function M:ctor()
	self.mId = GlobalNS.UiFormId.eUiTopXRankPanel;
	self.mData = GlobalNS.new(GlobalNS.TopXRankPanelNS.TopXRankPanelData);
    
    self.mDropBtn = nil;
    self.mDownBtn = nil;

    --listitem prefab
    self.mListitem_prefab = GlobalNS.new(GlobalNS.AuxPrefabLoader);
	self.mListitem_prefab:setIsNeedInsPrefab(false);

    --listitems数组
    self.listitems = { };
    self.honerimages = {};
    self.myhoner = nil;
end

function M:dtor()
	self.mDropBtn:dispose();
    self.mDownBtn:dispose();
end

function M:onInit()
    M.super.onInit(self);

    self.mDropBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mDropBtn:addEventHandle(self, self.onDropBtnClk, 0);

    self.mDownBtn = GlobalNS.new(GlobalNS.AuxButton);
	self.mDownBtn:addEventHandle(self, self.onDownBtnClk, 0);
end

function M:onReady()
    M.super.onReady(self);

    --topx
    self.topXBG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "TopXBG");
    local title = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.topXBG, "Title");
	self.mDropBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(title,"Drop_BtnTouch"));
    --获取ScrollRect的GameObject对象
    self.mScrollRect = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.topXBG, "ScrollRect");
    local viewport =  GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mScrollRect, "Viewport");
    --获取ScrollRect下Content中的RectTransform组件
    self.mRankContent = GlobalNS.UtilEngineWrap.getComByPath(viewport, "Content", "RectTransform");

    --获取MyRank的GameObject对象
    self.mMyRankArea = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.topXBG, "myrank");

    --加载listitem prefab
	self.mListitem_prefab:asyncLoad("UI/UiTopXRankPanel/TopxListItem.prefab", self, self.onPrefabLoaded, nil);

    --收起排行榜
    self.UpBG = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mGuiWin, "UP_bg");
    title = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.UpBG, "Title");
	self.mDownBtn:setSelfGo(GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(title,"Down_BtnTouch"));

    if #self.listitems == CtxExt.mPlayerData.mGameData.top10Count then
        self:showTopxRank();
    end
end

function M:createItems()
    --获取listitemprefab对象
    self.mListitemPrefab = self.mListitem_prefab:getPrefabTmpl();
    
    if nil ~= self.mListitemPrefab then
        for i=1, CtxExt.mPlayerData.mGameData.top10Count do
            --用listitemprefab生成GameObject对象
            local listitem = GlobalNS.UtilEngineWrap.Instantiate(self.mListitemPrefab);
            listitem.transform.parent = self.mRankContent;
            listitem.transform.localScale = Vector3.New(1.0, 1.0, 1.0);
    
            listitem.name = "Top" .. i;
    
            self.listitems[i] = listitem;
        end
    
        --滚动到起始位置，默认会在中间
        GlobalNS.UtilEngineWrap.GetComponent(self.mScrollRect, "ScrollRect").verticalNormalizedPosition = 1;
    end
end

function M:onPrefabLoaded(dispObj)
    self:createItems();
    if #self.listitems == CtxExt.mPlayerData.mGameData.top10Count then
        self:showTopxRank();
    end
end

function M:showTopxRank()
    --topx
    for i=1, CtxExt.mPlayerData.mGameData.top10Count do
        local listitem = self.listitems[i].transform;

        --荣誉
        local Honer = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.listitems[i], "rank");
        if i > 3 then
            Honer:SetActive(false);
        else
            Honer:SetActive(true);
            local honerTransform = GlobalNS.UtilEngineWrap.GetComponent(Honer, "RectTransform");
            local honer = GlobalNS.new(GlobalNS.AuxImage);
            honer:setSelfGo(Honer);
            if i == 1 then
                honerTransform.sizeDelta = Vector2.New(36, 26);
				honer:setSpritePath("DefaultSkin/SkyWarSkin/topx1.png", "topx1");
                --honer:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_gold");
            elseif i == 2 then
                honerTransform.sizeDelta = Vector2.New(24, 24);
				honer:setSpritePath("DefaultSkin/SkyWarSkin/topx2.png", "topx2");
                --honer:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_yin");
            else
                honerTransform.sizeDelta = Vector2.New(24, 24);
				honer:setSpritePath("DefaultSkin/SkyWarSkin/topx3.png", "topx3");
                --honer:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_tong");
            end
            self.honerimages[i] = honer;
         end

        --排名
        local Rank = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.listitems[i], "rank_Text");
        local Ranktext = GlobalNS.UtilEngineWrap.getComByPath(listitem, "rank_Text", "Text");
        if i <= 3 then
            Rank:SetActive(false);
        else
            Rank:SetActive(true);
            if i == CtxExt.mPlayerData.mGameData.top10_myrank then
                Ranktext.text = "<color=#32c832ff>"..i.."</color>";
            else
                Ranktext.text = "" .. i;
            end
        end

        --用户名
        local Name = GlobalNS.UtilEngineWrap.getComByPath(listitem, "name", "Text");        
        if i == CtxExt.mPlayerData.mGameData.top10_myrank then
            Name.text = "<color=#32c832ff>"..CtxExt.mPlayerData.mGameData.top10ranklist[i].m_name.."</color>";
        else
            Name.text = CtxExt.mPlayerData.mGameData.top10ranklist[i].m_name;
        end
    end

    --我的排名
    local myHoner = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mMyRankArea, "rank");
    local myrank = GlobalNS.UtilEngineWrap.TransFindChildByPObjAndPath(self.mMyRankArea, "rank_Text");
    if CtxExt.mPlayerData.mGameData.top10_myrank > 3 then
        myHoner:SetActive(false);
        myrank:SetActive(true);
        local myRanktext = GlobalNS.UtilEngineWrap.getComByPath(self.mMyRankArea, "rank_Text", "Text");
        myRanktext.text = "" .. CtxExt.mPlayerData.mGameData.top10_myrank;
    else
        myrank:SetActive(false);
        myHoner:SetActive(true);
        local myhonerTransform = GlobalNS.UtilEngineWrap.GetComponent(myHoner, "RectTransform");
        self.myhoner = GlobalNS.new(GlobalNS.AuxImage);
        self.myhoner:setSelfGo(myHoner);
        if CtxExt.mPlayerData.mGameData.top10_myrank == 1 then
            myhonerTransform.sizeDelta = Vector2.New(36, 26);
			self.myhoner:setSpritePath("DefaultSkin/SkyWarSkin/topx1.png", "topx1");
            --self.myhoner:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_gold");
        elseif CtxExt.mPlayerData.mGameData.top10_myrank == 2 then
            myhonerTransform.sizeDelta = Vector2.New(24, 24);
			self.myhoner:setSpritePath("DefaultSkin/SkyWarSkin/topx2.png", "topx2");
            --self.myhoner:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_yin");
        else
            myhonerTransform.sizeDelta = Vector2.New(24, 24);
			self.myhoner:setSpritePath("DefaultSkin/SkyWarSkin/topx3.png", "topx3");
            --self.myhoner:setSpritePath("DefaultSkin/GameOption/GameOption_RGB.png", "cup_tong");
        end
    end
    local myName = GlobalNS.UtilEngineWrap.getComByPath(self.mMyRankArea, "name", "Text");
    myName.text = CtxExt.mPlayerData.mGameData.mMyName;
end

function M:onDropBtnClk()
    --Ctx.mUiMgr:loadAndShow(GlobalNS.UiFormId.eUiConsoleDlg);
    self.topXBG:SetActive(false);
    self.UpBG:SetActive(true);
end

function M:onDownBtnClk()
    --Ctx.mUiMgr:exit(GlobalNS.UiFormId.eUiConsoleDlg);
    self.topXBG:SetActive(true);
    self.UpBG:SetActive(false);
end

function M:onShow()
    M.super.onShow(self);
end

function M:onHide()
    M.super.onHide(self);
end

function M:onExit()
    M.super.onExit(self);
    self:clearResource();
    self.mListitem_prefab:dispose();
end

function M:clearResource()
    if self.myhoner ~= nil then
        self.myhoner:dispose();
        self.myhoner = nil;
    end
    for i=1, #self.honerimages do
        self.honerimages[i]:dispose();
    end
    self.honerimages = {};

    for i=1, #self.listitems do
        local item = self.listitems[i];
        GlobalNS.UtilEngineWrap.Destroy(item);
    end
    self.listitems = { };
end

function M:updateUIData()
    self:clearResource();
    self:createItems();
    if #self.listitems == CtxExt.mPlayerData.mGameData.top10Count then
        self:showTopxRank();
    end
end

return M;