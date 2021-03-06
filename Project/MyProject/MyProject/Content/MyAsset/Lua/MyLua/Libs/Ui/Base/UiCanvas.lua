MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.Core.GObject");
MLoader("MyLua.Libs.Ui.Base.UiLayer");
MLoader("MyLua.Libs.Ui.Base.UiCanvasId");

M = GlobalNS.Class(GlobalNS.GObject);
M.clsName = "UiCanvas";
GlobalNS[M.clsName] = M;

function M:ctor()
	self.mName = "";
	self.mLayerList = GlobalNS.new(GlobalNS.MList);
end

function M:setGoName(name)
	self.mName = name;
end

function M:init()
	local layer = nil;
	local layerName = '';
	
	layer = GlobalNS.new(GlobalNS.UiLayer);
	self.mLayerList:add(layer);
	layerName = string.format("%s/%s", self.mName, GlobalNS.LayerId.ND_CV_UIBtmLayer);
	layer:setGoName(layerName);
	layer:init();
	
	layer = GlobalNS.new(GlobalNS.UiLayer);
	self.mLayerList:add(layer);
	layerName = string.format("%s/%s", self.mName, GlobalNS.LayerId.ND_CV_UIFirstLayer);
	layer:setGoName(layerName);
	layer:init();
	
	layer = GlobalNS.new(GlobalNS.UiLayer);
	self.mLayerList:add(layer);
	layerName = string.format("%s/%s", self.mName, GlobalNS.LayerId.ND_CV_UISecondLayer);
	layer:setGoName(layerName);
	layer:init();
	
	layer = GlobalNS.new(GlobalNS.UiLayer);
	self.mLayerList:add(layer);
	layerName = string.format("%s/%s", self.mName, GlobalNS.LayerId.ND_CV_UIThirdLayer);
	layer:setGoName(layerName);
	layer:init();
	
	layer = GlobalNS.new(GlobalNS.UiLayer);
	self.mLayerList:add(layer);
	layerName = string.format("%s/%s", self.mName, GlobalNS.LayerId.ND_CV_UIForthLayer);
	layer:setGoName(layerName);
	layer:init();
	
	layer = GlobalNS.new(GlobalNS.UiLayer);
	self.mLayerList:add(layer);
	layerName = string.format("%s/%s", self.mName, GlobalNS.LayerId.ND_CV_UITopLayer);
	layer:setGoName(layerName);
	layer:init();
end

function M:getLayerGo(layerId)
	return self.mLayerList:at(layerId):getLayerGo();
end

return M;