#include "MyProject.h"
#include "MyBluePrintToCppFunctionLibrary.h"
#include "MyBluePrintBase.h"
#include "Ctx.h"
#include "UtilEngineWrap.h"
#include "EngineData.h"
#include "UMGWidget.h"				// UUMGWidget

UMyBluePrintToCppFunctionLibrary::UMyBluePrintToCppFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UMyBluePrintBase* UMyBluePrintToCppFunctionLibrary::getBPCtx()
{
	//return GBPCtx.get();
	return GBPCtx;
}

APawn* UMyBluePrintToCppFunctionLibrary::getFirstCharacter()
{
	return UtilEngineWrap::getFirstCharacter();
}

AMyPlayerControllerBase* UMyBluePrintToCppFunctionLibrary::GetPlayerController()
{
	return UtilEngineWrap::GetPlayerController();
}

UUMGWidget* UMyBluePrintToCppFunctionLibrary::createWidget(UClass* WidgetClass)
{
	UUMGWidget* WidgetObject = nullptr;

	WidgetObject = UtilEngineWrap::CreateWidget<UUMGWidget>(GEngineData->getMainPlayerController(), WidgetClass);

	return WidgetObject;
}

UObject* UMyBluePrintToCppFunctionLibrary::newObjectFromBlueprint(UClass* cls)
{
	APlayerController* playerController = (APlayerController*)UtilEngineWrap::GetPlayerController();
	UObject* tempObject = NewObject<UObject>(playerController, cls);

	return tempObject;
}