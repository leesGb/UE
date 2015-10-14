#ifndef __UIMGR_H
#define __UIMGR_H

#include <map>
#include <vector>
#include "UIFormID.h"

class UFormBase;
class UICanvas;
class UIAttrSystem;

/**
 * @brief 所有 UI 管理
 * 1. 对于新创建的Form对象，其所属的层是由其ID决定的
 * 2. UI 设计原则，主要界面是资源创建完成才运行逻辑，小的共享界面是逻辑和资源同时运行，因为 MVC 结构实在是要写很多代码，因此主要界面不适用 MVC 结构
 */
class UIMgr
{
protected:
	std::map<UIFormID, UFormBase*> m_id2FormDic;
	std::vector<UICanvas*> m_canvasList;
	UIAttrSystem* m_UIAttrs;

	std::map<UIFormID, UILoadingItem> m_ID2CodeLoadingItemDic;         // 记录当前代码正在加载的项
	Dictionary<UIFormID, UILoadingItem> m_ID2WidgetLoadingItemDic;         // 记录当前窗口控件正在加载的项

	List<UIFormID> m_tmpList = new List<UIFormID>();
	GameObject m_sceneUIRootGo;           // 每一个场景都会有一个这样的节点，专门放一些 Scene 中 UI 的一些信息


public:
	UIMgr();
	template <class T>
	UFormBase* loadForm(UIFormID formID);

	template <class T>
	T* getForm(UIFormID formID);
};

#include "UIMgr.inl"			// 模板具体的实现

#endif				// __UIMANAGER_H