#include "MyProject.h"
#include "UMGForm.h"
#include "Ctx.h"
#include "EngineApi.h"

void UUMGForm::loadUWidget(const TCHAR* name)
{
	UClass* widgetClass = StaticLoadClass(UUserWidget::StaticClass(), NULL, name);
	if (widgetClass != NULL)
	{
		//m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, GEngine->GameViewport->GetWorld()->GetGameInstance()));
		//m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, MyCtx::getSingletonPtr()->getGameInstance()));

		// warning C4996: 'StaticConstructObject': StaticConstructObject is deprecated, please use NewObject instead. For internal CoreUObject module usage, please use StaticConstructObject_Internal. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, Ctx::getSingletonPtr()->getEngineApi()->getGameInstance()));
		// 直接构造一个抽象类是报错误的
		// NewObject<UUserWidget>();
		// 构造一个类的子类，最新的 api 如下就可以了
		m_umgWidget = NewObject<UUserWidget>(g_pEngineApi->getGameInstance(), widgetClass);
	}
}

UUMGForm::UUMGForm()
	:UFormBase()
{
	m_exitMode = true;
	m_bHideOnCreate = false;
	m_bLoadWidgetRes = false;
	m_bReady = false;
	m_bBlurBg = false;
	m_bHandleExitBtn = false;
	m_alignVertial = (int)WindowAnchor.CENTER;
	m_alignHorizontal = (int)WindowAnchor.CENTER;
}

UIFormID UUMGForm::getFormID()
{
	return m_id;
}

void UUMGForm::setFormID(UIFormID value)
{
	m_id = value;
}

bool UUMGForm::getHideOnCreate()
{
	return m_bHideOnCreate;
}

void UUMGForm::getHideOnCreate(bool value)
{
	m_bHideOnCreate = value;
}

bool UUMGForm::getExitMode()
{
	return m_exitMode;
}

void UUMGForm::setExitMode(bool value)
{
	m_exitMode = value;
}

bool UUMGForm::getLoadWidgetRes()
{
	return m_bLoadWidgetRes;
}

void UUMGForm::setBLoadWidgetRes(bool value)
{
	m_bLoadWidgetRes = true;
}

bool getBReady()
{
	return m_bReady;
}

std::string getFormName()
{
	return m_formName;
}
void setFormName(std::string value)
{
	m_formName = value;
}

LuaCSBridgeForm* getLuaCSBridgeForm()
{
	return m_luaCSBridgeForm;
}

void getLuaCSBridgeForm(LuaCSBridgeForm* value)
{
	m_luaCSBridgeForm = value;
}

void init()
{
	onInit();
}

void show()
{
	Ctx.m_instance.m_uiMgr.showForm(m_id);
}

//private void hide()
//{
//    Ctx.m_instance.m_uiMgr.hideForm(m_id);
//}

void exit()
{
	Ctx.m_instance.m_uiMgr.exitForm(m_id);
}

// 界面代码创建后就调用
void onInit()
{
	if (m_luaCSBridgeForm != null)
	{
		m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_INIT);
	}
	//if (m_bLoadWidgetRes)
	//{
	// 默认会继续加载资源
	Ctx.m_instance.m_uiMgr.loadWidgetRes(this.id);
	//}
}

// 第一次显示之前会调用一次
void onReady()
{
	if (m_luaCSBridgeForm != null)
	{
		m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_READY);
	}

	m_bReady = true;
	if (m_bHandleExitBtn)
	{
		UtilApi.addEventHandle(m_GUIWin.m_uiRoot, "BtnClose", onExitBtnClick); // 关闭事件
	}
}

// 每一次显示都会调用一次
void onShow()
{
	if (m_luaCSBridgeForm != null)
	{
		m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_SHOW);
	}

	if (m_bBlurBg)
	{
		Ctx.m_instance.m_uiMgr.showForm(UIFormID.eUIBlurBg);        // 显示模糊背景界面
	}
	//adjustPosWithAlign();
}

// 每一次隐藏都会调用一次
void onHide()
{
	if (m_luaCSBridgeForm != null)
	{
		m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_HIDE);
	}

	if (m_bBlurBg)
	{
		Ctx.m_instance.m_uiMgr.exitForm(UIFormID.eUIBlurBg);
	}
}

// 每一次关闭都会调用一次
void onExit()
{
	if (m_luaCSBridgeForm != null)
	{
		m_luaCSBridgeForm.CallMethod(LuaCSBridgeForm.ON_EXIT);
	}

	if (m_bBlurBg)
	{
		Ctx.m_instance.m_uiMgr.exitForm(UIFormID.eUIBlurBg);
	}
}

bool isVisible()
{
	return m_GUIWin.m_uiRoot.activeSelf;        // 仅仅是自己是否可见
}

/*
* stage的大小发生变化后，这个函数会被调用。子类可重载这个函数
*/
void onStageReSize()
{
	adjustPosWithAlign();
}

void adjustPosWithAlign()
{
	PointF pos = computeAdjustPosWithAlign();
	this.x = pos.x;
	this.y = pos.y;
}

PointF computeAdjustPosWithAlign()
{
	PointF ret = new PointF(0, 0);
	int widthStage = 0;
	int heightStage = 0;
	if (m_alignVertial == (int)WindowAnchor.CENTER)
	{
		ret.y = (heightStage - this.m_height) / 2;
	}
	else if (m_alignVertial == (int)WindowAnchor.TOP)
	{
		ret.y = this.m_marginTop;
	}
	else
	{
		ret.y = heightStage - this.m_height - this.m_marginBottom;
	}

	if (m_alignHorizontal == (int)WindowAnchor.CENTER)
	{
		ret.x = (widthStage - this.m_width) / 2;
	}
	else if (m_alignHorizontal == (int)WindowAnchor.LEFT)
	{
		ret.x = m_marginLeft;
	}
	else
	{
		ret.x = widthStage - this.m_width - m_marginRight;
	}
	return ret;
}

// 按钮点击关闭
void onExitBtnClick()
{
	exit();
}

void registerBtnClickEventByList(string[] btnList)
{
	foreach(var path in btnList)
	{
		addClick(m_GUIWin.m_uiRoot, path);
	}
}

void registerImageClickEventByList(string[] imageList)
{

}

void registerWidgetEvent()
{
	string[] pathArr = m_luaCSBridgeForm.getTable2StrArray("BtnClickTable");
	foreach(var path in pathArr)
	{
		addClick(m_GUIWin.m_uiRoot, path);
	}
}

void onBtnClk(GameObject go_)
{
	if (m_luaCSBridgeForm != null)
	{
		if (m_go2Path.ContainsKey(go_))
		{
			m_luaCSBridgeForm.handleUIEvent("onBtnClk", m_formName, m_go2Path[go_].m_path);
		}
	}

	// 测试全局分发事件
	// Ctx.m_instance.m_globalEventMgr.eventDispatchGroup.dispatchEvent((int)eGlobalEventType.eGlobalTest, null);
}

void addClick(GameObject go, string path)
{
	UtilApi.addEventHandle(go, path, onBtnClk);
	GameObject btnGo = UtilApi.TransFindChildByPObjAndPath(go, path);
	if (btnGo = null)
	{
		if (!m_go2Path.ContainsKey(btnGo))
		{
			m_go2Path[btnGo] = new GOExtraInfo();
			m_go2Path[btnGo].m_path = path;
		}
	}
}

void removeClick(GameObject go, string path)
{
	UtilApi.removeEventHandle(go, path);
	GameObject btnGo = UtilApi.TransFindChildByPObjAndPath(go, path);
	if (btnGo != null)
	{
		if (m_go2Path.ContainsKey(btnGo))
		{
			m_go2Path.Remove(btnGo);
		}
	}
}