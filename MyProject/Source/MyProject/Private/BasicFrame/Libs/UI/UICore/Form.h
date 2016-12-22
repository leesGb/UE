#pragma once

#include "MyProject.h"
#include "Window.h"
#include <string>
#include "UIFormId.h"
#include "PointF.h"

#include "Form.generated.h"

class UUserWidget;
class PointF;

UCLASS(config = Game)
class UForm : public UWindow
{
	GENERATED_BODY()

protected:
	//TSharedPtr<SWidget> m_outUserSlateWidget;
	//TSharedRef<SWidget> m_rootWidget;

	bool mIsExitMode;               // 关闭退出模式
	bool mIsHideOnCreate;         // 创建后是否隐藏
	UIFormId mId;
	bool mIsLoadWidgetRes;                // 是否应该加载窗口资源
	bool mIsReady;            // 是否准备就绪

	bool mIsBlurBg;       // 是否模糊背景
	bool mIsHandleExitBtn;       // 是否关联关闭按钮

	// LuaCSBridgeForm mLuaCSBridgeForm;
	std::string mFormName;            // 这个是 Lua 中传的标识符，会传给 Lua 使用，客户端自己不用
	//std::map<GameObject, GoExtraInfo> mGo2Path;

public:
	UForm(const FObjectInitializer& ObjectInitializer);

	void loadUWidget(const TCHAR* name);
	UIFormId getId();
	void setId(UIFormId value);
	bool getHideOnCreate();
	void setHideOnCreate(bool value);
	bool getExitMode();
	void setExitMode(bool value);
	bool getIsLoadWidgetRes();
	void setIsLoadWidgetRes(bool value);
	bool getBReady();
	std::string getFormName();
	void setFormName(std::string value);
	//LuaCSBridgeForm* UUMGForm::getLuaCSBridgeForm();
	//void UUMGForm::getLuaCSBridgeForm(LuaCSBridgeForm* value);
	void init();
	void show();
	//private void UUMGForm::hide();
	void exit();
	// 界面代码创建后就调用
	void onInit();
	// 第一次显示之前会调用一次
	void onReady();
	// 每一次显示都会调用一次
	void onShow();
	// 每一次隐藏都会调用一次
	void onHide();
	// 每一次关闭都会调用一次
	void onExit();
	bool isVisible();
	/*
	* stage的大小发生变化后，这个函数会被调用。子类可重载这个函数
	*/
	void onStageReSize();
	void adjustPosWithAlign();
	PointF* computeAdjustPosWithAlign();
	// 按钮点击关闭
	void onExitBtnClick();
	//void registerBtnClickEventByList(std::string[] btnList);
	//void registerImageClickEventByList(string[] imageList);
	//void registerWidgetEvent();
	//void onBtnClk(GameObject go_);
	//void addClick(GameObject go, string path);
	//void removeClick(GameObject go, string path);
	bool getIsReady();
};