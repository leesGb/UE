#pragma once

#include "MyProject.h"
#include "MyBluePrintToCppFunctionLibrary.generated.h"

class UMyBluePrintBase;

UCLASS()
class UMyBluePrintToCppFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UMyBluePrintToCppFunctionLibrary(const FObjectInitializer& ObjectInitializer);

	/**
	 * @def BlueprintPure BluePrint 可以调用
	 * @def Category BluePrint 中 Palette 中显示的标签
	 */
	UFUNCTION(BlueprintPure, Category = "MyBluePrintToCppFunctionLibrary")
	static UMyBluePrintBase* getBPCtx();

	UFUNCTION(BlueprintPure, Category = "MyBluePrintToCppFunctionLibrary")
	static APawn* getFirstCharacter();	// 获取第一个 ACharacter ，就是主角自己

	UFUNCTION(BlueprintPure, Category = "MyBluePrintToCppFunctionLibrary")
	static AMyPlayerControllerBase* GetPlayerController();

	UFUNCTION(BlueprintPure, Category = "MyBluePrintToCppFunctionLibrary")
	static UUMGWidget* createWidget(UClass* WidgetClass);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = "MyBluePrintToCppFunctionLibrary")
	static UObject* newObjectFromBlueprint(UClass* cls);
};