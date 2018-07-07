MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");
MLoader("MyLua.Libs.Core.GObject");

local M = GlobalNS.StaticClass();
M.clsName = "NoDestroyId";
GlobalNS[M.clsName] = M;

function M.ctor()
	
end

M.ND_CV_NoDestroy = "NoDestroy";

M.ND_CV_UIFirstCanvas = "UIFirstCanvas";
M.ND_CV_UISecondCanvas = "UISecondCanvas";

M.ND_CV_UIBtmLayer = "UIBtmLayer";
M.ND_CV_UIFirstLayer = "UIFirstLayer";
M.ND_CV_UISecondLayer = "UISecondLayer";
M.ND_CV_UIThirdLayer = "UIThirdLayer";
M.ND_CV_UIForthLayer = "UIForthLayer";
M.ND_CV_UITopLayer = "UITopLayer";

M.ctor();

-----------------------
M = GlobalNS.StaticClass();
M.clsName = "LayerPath";
GlobalNS[M.clsName] = M;

function M.ctor()
	
end

function M.init()
	M.mNoDestroyGo = GlobalNS.UtilEngineWrap.GoFindChildByName(GlobalNS.NoDestroyId.ND_CV_NoDestroy);
	M.mUIFirstCanvasGo = GlobalNS.UtilEngineWrap.GoFindChildByName(GlobalNS.NoDestroyId.ND_CV_UIFirstCanvas);
	M.mUISecondCanvasGo = GlobalNS.UtilEngineWrap.GoFindChildByName(GlobalNS.NoDestroyId.ND_CV_UISecondCanvas);
end

return M;