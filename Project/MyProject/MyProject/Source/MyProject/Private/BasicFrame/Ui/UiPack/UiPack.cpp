#include "MyProject.h"
#include "UiPack.h"
#include "Prequisites.h"
#include "BinaryLoadItem.h"
#include "TableSys.h"
#include "DataAssetLoadItem.h"

UUiPack::UUiPack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//loadUWidget(TEXT("/Game/Blueprints/NewWidgetBlueprint.NewWidgetBlueprint_C"));
	//m_umgWidget->AddToViewport();
	//UtilEngineWrap::addEventHandle((UButton*)m_umgWidget->GetWidgetFromName("Button_16"), (UObject*)this, "OnConfirmGeneric");

	//TSharedPtr<SWidget> m_outUserSlateWidget;
	//TSharedRef<SWidget> m_rootWidget = m_umgWidget->MakeViewportWidget(m_outUserSlateWidget);
	//GEngine->GameViewport->AddViewportWidgetContent(m_rootWidget);

	//UButton* ccc = (UButton*)m_umgWidget->GetWidgetFromName("Button_14");
	//TScriptDelegate<FWeakObjectPtr> ddd;
	//ddd.BindUFunction((UObject *)this, "OnConfirmGeneric");
	//ccc->OnClicked.Add(ddd);
}

void UUiPack::onReady()
{
	loadUWidget(TEXT("/Game/Blueprints/NewWidgetBlueprint.NewWidgetBlueprint_C"));
	mWinRender->mUiRoot->AddToViewport();
	UtilEngineWrap::addEventHandle((UButton*)mWinRender->mUiRoot->GetWidgetFromName("Button_16"), (UObject*)this, "OnConfirmGeneric");
}

void UUiPack::OnConfirmGeneric()
{
	////UBinaryLoadItem* pBinaryLoadItem = LoadObject<UBinaryLoadItem>(NULL, TEXT("/Game/Table/aaa"), NULL, LOAD_None, NULL);
	//FString Filename = FString::Printf(TEXT("%s%s"), *FPaths::GameContentDir(), TEXT("/Table/aaa.tbl"));
	//UBinaryLoadItem* pBinaryLoadItem = new UBinaryLoadItem();
	////pBinaryLoadItem->loadFile(IFileManager::Get().ConvertToRelativePath(*Filename));
	//pBinaryLoadItem->loadFile(Filename);
	//delete pBinaryLoadItem;

	GTableSys->getItem(TableId::TABLE_OBJECT, 100);

	//UPackage* Pkg = CreatePackage(NULL, NULL);
	//EObjectFlags Flags = RF_Public | RF_Standalone;
	//UObject* pObj = ConstructObject<UDataAssetLoadItem>(UDataAssetLoadItem::StaticClass(), Pkg, "/Game/Table/aaa", Flags);

	UPackage* tblPkg = CreatePackage(NULL, TEXT("/Game/Table/ObjectBase_client"));
	UDataAssetLoadItem* ObjectPtr = LoadObject<UDataAssetLoadItem>(tblPkg, TEXT("/Game/Table/ObjectBase_client"));
}