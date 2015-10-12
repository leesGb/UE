#include "MyProject.h"
#include "UITestCanvas.h"
#include "Common.h"
#include "BinaryLoadItem.h"
#include "Ctx.h"
#include "TableSys.h"
#include "DataAssetLoadItem.h"

UUITestCanvas::UUITestCanvas(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UUITestCanvas::onReady()
{
	//loadCanvas();
	//loadNoCanvas();
	loadNamedSlot();
	//loadOverlay();
	//EngineApi::addEventHandle((UButton*)m_umgWidget->GetWidgetFromName("Button_32"), (UObject*)this, "OnConfirmGeneric");
}

void UUITestCanvas::OnConfirmGeneric()
{
	//g_pTableSys->getItem(TableID::TABLE_OBJECT, 100);

	//UPackage* tblPkg = CreatePackage(NULL, TEXT("/Game/Table/ObjectBase_client"));
	//UDataAssetLoadItem* ObjectPtr = LoadObject<UDataAssetLoadItem>(tblPkg, TEXT("/Game/Table/ObjectBase_client"));
}

void UUITestCanvas::loadCanvas()
{
	loadUWidget(TEXT("/Game/UMG/UITestCanvas_Canvas.UITestCanvas_Canvas_C"));
	m_umgWidget->AddToViewport();
}

void UUITestCanvas::loadNoCanvas()
{
	loadUWidget(TEXT("/Game/UMG/UITestCanvas_NoCanvas.UITestCanvas_NoCanvas_C"));
	m_umgWidget->AddToViewport();
}

void UUITestCanvas::loadCanvasWithNoCanvas()
{
	
}

void UUITestCanvas::loadNamedSlot()
{
	loadUWidget(TEXT("/Game/UMG/UITestNamedSlot.UITestNamedSlot_C"));
	//loadUWidget(TEXT("/Game/Blueprints/NewWidgetBlueprint.NewWidgetBlueprint_C"));
	m_umgWidget->AddToViewport();	// һ��Ҫ�� AddToViewport ��Ȼ���ٻ�ȡ�ؼ������� GetWidgetFromName ��ʱ��ᱨ��
	// Ŀǰ�Ѿ��е� NamedSlot �� "NamedSlot_28"
	m_umgWidget->GetSlotNames(m_namedSlotArr);
	m_namedSlot = (UNamedSlot*)(m_umgWidget->GetWidgetFromName("NamedSlot_28"));
	//UWidget* widget = m_umgWidget->GetWidgetFromName("Button_16");
}

void UUITestCanvas::loadOverlay()
{
	loadUWidget(TEXT("/Game/UMG/UITestOveray.UITestOveray_C"));
	m_umgWidget->AddToViewport();
	// Overlay_17 �Ѿ��е� Overlay 
	//m_overlay = (UOverlay*)(m_umgWidget->GetWidgetFromName("Overlay_17"));
	UWidget* widget = m_umgWidget->GetWidgetFromName("Button_32");
}