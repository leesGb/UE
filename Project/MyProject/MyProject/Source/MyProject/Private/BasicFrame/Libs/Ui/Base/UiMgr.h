#ifndef __UiMgr_H
#define __UiMgr_H

#include "MDictionary.h"
#include "MList.h"
#include "UiFormId.h"
#include "EventDispatchDelegate.h"
#include "UiCanvas.h"
#include "UiLayer.h"
#include "UiAttrItem.h"
#include "UiAttrSystem.h"
#include "Form.h"
#include "GObject.h"
#include "TypeDef.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

class UForm;

MY_BEGIN_NAMESPACE(MyNS)

class UiCanvas;
class UiAttrSystem;
class UiLoadingItem;
class IDispatchObject;
class ClassAssetInsRes;

/**
 * @brief 所有 UI 管理
 * 1. 对于新创建的Form对象，其所属的层是由其formId决定的
 * 2. UI 设计原则，主要界面是资源创建完成才运行逻辑，小的共享界面是逻辑和资源同时运行，因为 MVC 结构实在是要写很多代码，因此主要界面不适用 MVC 结构
 */
class UiMgr : public GObject
{
	M_DECLARE_CLASS(UiMgr, GObject)

protected:
	MDictionary<UiFormId, UForm*> mId2FormDic;
	MList<UiCanvas*> mCanvasList;
	UiAttrSystem* mUiAttrSystem;

	MDictionary<UiFormId, UiLoadingItem*> mId2CodeLoadingItemDic;         // 记录当前代码正在加载的项
	MDictionary<UiFormId, UiLoadingItem*> mId2WidgetLoadingItemDic;         // 记录当前窗口控件正在加载的项

	MList<UiFormId> mTmpList;
	//GameObject mSceneUIRootGo;           // 每一个场景都会有一个这样的节点，专门放一些 Scene 中 UI 的一些信息

public:
	UiMgr();

	void init();
	void dispose();

	template <class T>
	T* loadForm(UiFormId formId);

	template <class T>
	T* getForm(UiFormId formId);

	template <class T>
	T* loadAndShow(UiFormId formId);

	void createCanvas();
	void findCanvasActor();

	void showForm(UiFormId formId);
	void _showFormInternal(UiFormId formId);
	void _hideFormInternal(UiFormId formId);
	void exitForm(UiFormId formId, bool bForce = false);
	void _exitFormInternal(UiFormId formId);
	void addForm(UForm* form);

	UiLayer* getLayer(UiCanvasId canvasID, UiLayerId layerId);

	void addFormNoReady(UForm* form);
	bool hasForm(UiFormId formId);

	void loadWidgetRes(UiFormId formId);
	void loadFromFile(std::string reaPath, EventDispatchDelegate onLoadEventHandle);

	void onCodeLoadEventHandle(uint eventId, IDispatchObject* dispObj);
	void onWidgetLoadEventHandle(uint eventId, IDispatchObject* dispObj);
	void onCodeloadedByRes(ClassAssetInsRes* res);
	void onCodeLoadedByForm(UForm* form);
	void onWidgetloadedByRes(ClassAssetInsRes* res);
	void onWidgetAuxUIClassloadedByRes(uint eventId, IDispatchObject* res);

	void onResize(int viewWidth, int viewHeight);

	void exitAllForm();
	void findSceneUIRootActor();
	//void unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe);
};

MY_END_NAMESPACE

#include "UiMgr.inl"			// 模板具体的实现

// 如果 UiMgr.inl 中有包含系统头文件，相当于系统类声明的时候都包含名字空间了，与系统类的定义不相同，导致编译错误
// MY_END_NAMESPACE

#endif				// __UiMgr_H