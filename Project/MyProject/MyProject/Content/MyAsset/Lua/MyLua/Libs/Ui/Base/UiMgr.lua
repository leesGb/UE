MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");
MLoader("MyLua.Libs.Core.ClassLoader");
MLoader("MyLua.Libs.DataStruct.MStack");
MLoader("MyLua.Libs.DataStruct.MDictionary");
MLoader("MyLua.Libs.Ui.Base.UiFormId");
MLoader("MyLua.Libs.Ui.Base.UiCanvas");
MLoader("MyLua.Libs.Auxiliary.AuxLoader.AuxUiPrefabLoader");

local M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "UiMgr";
GlobalNS[M.clsName] = M;

function M:ctor()
    self.mFormDic = {};
    self.mCurFormIndex = -1;
    self.mFormIdStack = GlobalNS.new(GlobalNS.MStack);
	self.mFormId2LoadItemDic = GlobalNS.new(GlobalNS.MDictionary);
	
	self.mFormBaseI = 10000;		-- Form Base 起始的 Id,需要与 CS 中 Form Id 不一样，否则会覆盖 CS 中的设置
	self.mUniqueNumIdGen = GlobalNS.new(GlobalNS.UniqueNumIdGen, self.mFormBaseI); 	-- FormId 唯一 Id 生成
end

function M:dtor()

end

function M:init()
	-- UiFormId 初始化构造操作
	GlobalNS.UiFormId.init();
	-- 属性系统初始化
	GlobalNS.UiAttrSystem.init();
	self:initCanvas();
end

function M:initCanvas()
    if(self.mCanvasList == nil) then
        self.mCanvasList = GlobalNS.new(GlobalNS.MList);
        
        local canvas = nil;
        -- eBtnCanvas，原来默认的放在这个上
        canvas = GlobalNS.new(GlobalNS.UiCanvas);
        self.mCanvasList:add(canvas);
        canvas:setGoName(GlobalNS.LayerId.ND_CV_UIFirstCanvas);
        canvas:init();
        
        -- eFirstCanvas
        canvas = GlobalNS.new(GlobalNS.UiCanvas);
        self.mCanvasList:add(canvas);
        canvas:setGoName(GlobalNS.LayerId.ND_CV_UISecondCanvas);
        canvas:init();
    end
end

function M:getLayerGo(canvasId, layerId)
    -- 默认放在最底下的 Canvas，第二层
    if(canvasId == nil) then
        canvasId = GlobalNS.UiCanvasId.eUIFirstCanvas;
    end
    if(layerId == nil) then
        layerId = GlobalNS.UiLayerId.eUISecondLayer;
    end
    GlobalNS.UtilEngineWrap.assert(canvasId < self.mCanvasList:count());
    return self.mCanvasList:at(canvasId):getLayerGo(layerId);
end

function M:showForm(formId)
    -- 如果当前显示的不是需要显示的
	-- 保证没有在显示之前删除
	if(self.mFormDic[formId] ~= nil) then
		if(self.mCurFormIndex ~= formId) then
			local curFormIndex_ = self.mCurFormIndex;
			self:showFormNoClosePreForm(formId);
			self.mCurFormIndex = curFormIndex_;
			
			self:pushAndHideForm(formId);
			self.mCurFormIndex = formId;
		end
	end
end

function M:showFormNoClosePreForm(formId)
    if(self.mFormDic[formId] ~= nil) then
		if(not self.mFormDic[formId]:isVisible()) then
			self.mFormDic[formId]:onShow();
			if(self.mFormDic[formId]:isReady()) then
				GlobalNS.UtilEngineWrap.SetActive(self.mFormDic[formId].mGuiWin, true);
			end
		end
        self.mCurFormIndex = formId;
    end
    
    self.mFormIdStack:removeAllEqual(formId);
end

-- 仅仅加载 lua 脚本，不加载资源
function M:loadFormScript(formId, param)
    if(self.mFormDic[formId] == nil) then
        local codePath = GlobalNS.UiAttrSystem[formId].mLuaScriptPath;
        local formCls = GlobalNS.ClassLoader.loadClass(codePath);
        self.mFormDic[formId] = GlobalNS.new(formCls, param);
        self.mFormDic[formId]:onInit();
    end
end

-- 加载脚本并且加载资源
function M:loadForm(formId, param)
    if(self.mFormDic[formId] == nil) then
        self:loadFormScript(formId, param);
    end
    
    if(not self:hasLoadItem(formId)) then
		local uiPrefabLoader = GlobalNS.new(GlobalNS.AuxUiPrefabLoader);
		uiPrefabLoader:setIsNeedInsPrefab(true);
		uiPrefabLoader:setIsInsNeedCoroutine(false);
		
		self.mFormId2LoadItemDic:add(formId, uiPrefabLoader);
		uiPrefabLoader:setFormId(formId);
		uiPrefabLoader:asyncLoad(GlobalNS.UiAttrSystem[formId].mWidgetPath, self, self.onFormPrefabLoaded, nil);
    end
end

function M:loadAndShow(formId, param)
    if(self.mFormDic[formId] == nil or not self:hasLoadItem(formId)) then
        self:loadForm(formId, param);
    end
	if(self.mFormDic[formId] ~= nil and not self.mFormDic[formId]:isHideOnCreate()) then
		self:showForm(formId);
	end
    return self.mFormDic[formId];
end

function M:hideForm(formId)
    local bFormVisible = false;
    local form = self.mFormDic[formId];
    if(form ~= nil) then
        bFormVisible = form:isVisible();
    end
    
    self:hideFormNoOpenPreForm(formId);
    
    -- 只有当前界面是显示的时候，关闭这个界面才打开之前的界面
    if(bFormVisible) then
        -- 显示之前隐藏的窗口
        self:popAndShowForm(formId);
    end
end

function M:hideFormNoOpenPreForm(formId)
    local form = self.mFormDic[formId];
    if(form.mGuiWin ~= nil and GlobalNS.UtilEngineWrap.IsActive(form.mGuiWin)) then
        form:onHide();
        GlobalNS.UtilEngineWrap.SetActive(form.mGuiWin, false);
        self.mCurFormIndex = -1;
    end
end

function M:exitForm(formId)
    local bFormVisible = false;
    local form = self.mFormDic[formId];
    if(form ~= nil) then
        bFormVisible = form:isVisible();
    end
    
    self:exitFormNoOpenPreForm(formId);
    
    -- 只有当前界面是显示的时候，关闭这个界面才打开之前的界面
    if(bFormVisible) then
        -- 显示之前隐藏的窗口
        self:popAndShowForm(formId);
    end
end

-- 关闭当前窗口，不用打开之前的窗口
function M:exitFormNoOpenPreForm(formId)
    local form = self.mFormDic[formId];
    -- 关闭当前窗口
    if(form ~= nil) then
        form:onHide();
        form:onExit();
        GlobalNS.delete(form);
        self:unloadLoadItem(formId);
        self.mFormDic[formId] = nil;
        self.mCurFormIndex = -1;
    end
    
    self.mFormIdStack:removeAllEqual(formId);
end

-- 弹出并且显示界面
function M:popAndShowForm(formId)
    -- 显示之前隐藏的窗口
    if(GlobalNS.UiAttrSystem[formId].mPreFormModeWhenClose == GlobalNS.PreFormModeWhenClose.eSHOW) then
        local curFormIndex_ = self.mFormIdStack:pop();
        if(curFormIndex_ == nil) then
            self.mCurFormIndex = -1;
        else
            self:showFormNoClosePreForm(curFormIndex_);
        end
    end
end

function M:pushAndHideForm(formId)
    if(GlobalNS.UiAttrSystem[formId].mPreFormModeWhenOpen == GlobalNS.PreFormModeWhenOpen.eCLOSE) then
        if(self.mCurFormIndex >= 0) then
            self:exitFormNoOpenPreForm(self.mCurFormIndex);
        end
    elseif(GlobalNS.UiAttrSystem[formId].mPreFormModeWhenOpen == GlobalNS.PreFormModeWhenOpen.eHIDE) then
        if(self.mCurFormIndex >= 0) then
            -- 将当前窗口 Id 保存
            self.mFormIdStack:push(self.mCurFormIndex);
            -- 隐藏当前窗口
            self:hideFormNoOpenPreForm(self.mCurFormIndex);
        end
    end
end

function M:getForm(formId)
    return self.mFormDic[formId];
end

function M:hasForm(formId)
    local has = false;
    for _, value in pairs(self.mFormDic) do
        if(value ~= nil) then
            has = true;
            break;
        end
    end
    
    return has;
end

function M:hasLoadItem(formId)
	return self.mFormId2LoadItemDic:containsKey(formId);
end

function M:unloadLoadItem(formId)
	if(self.mFormId2LoadItemDic:containsKey(formId)) then
		self.mFormId2LoadItemDic:value(formId):dispose();
		self.mFormId2LoadItemDic:remove(formId);
	end
end

-- dispObj : AuxUiPrefabLoader
function M:onFormPrefabLoaded(dispObj)
	local formId = dispObj:getFormId();
	if(self.mFormDic[formId] ~= nil) then
		local parent = self:getLayerGo(GlobalNS.UiAttrSystem[self.mFormDic[formId].mId].mCanvasId, GlobalNS.UiAttrSystem[self.mFormDic[formId].mId].mLayerId);
        self.mFormDic[formId].mGuiWin = self.mFormId2LoadItemDic:value(formId):getSelfGo();
		GlobalNS.UtilEngineWrap.SetParent(self.mFormDic[formId].mGuiWin, parent, false);
        GlobalNS.UtilEngineWrap.SetActive(self.mFormDic[formId].mGuiWin, false);     -- 加载完成后先隐藏，否则后面 showForm 判断会有问题
        self.mFormDic[formId]:onReady();
		if(self.mFormDic[formId]:isVisible()) then
			GlobalNS.UtilEngineWrap.SetActive(self.mFormDic[formId].mGuiWin, true);
		end
	else
		self.mFormId2LoadItemDic:value(formId):dispose();
		self.mFormId2LoadItemDic:remove(formId);
	end
end

return M;