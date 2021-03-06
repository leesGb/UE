#pragma once

#include "UMGForm.h"
#include "AuxButton.h"
#include "MySharedPointer.h"
#include "TypeDef.h"

#include "UIFunctionBar.generated.h"

using namespace MyNS;

namespace MyNS
{
	class IDispatchObject;
}

using namespace MyNS;

UCLASS(config = Game)
class UUiFunctionBar : public UUMGForm
{
	GENERATED_BODY()

protected:
	MySharedPtr<AuxButton> mTestButton;
	AuxButton* mTestComBtn;
	AuxButton* mTestLoadTextureBtn;
	AuxButton* mTestLoadMaterialBtn;
	AuxButton* mTestChangeMaterialBtn;

public:
	UUiFunctionBar(const FObjectInitializer& ObjectInitializer);

public:
	virtual void onInit() override;
	virtual void onReady() override;
	virtual void onExit() override;

public:
	// UFunction* UObject::FindFunction( FName InName ) const
	// 绑定到 UMG 中的函数，一定要添加到虚拟机中，因为需要从 FindFunction 接口去虚拟机中去查找这个接口，如果不添加，就不能查找到
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestButtonTouch();
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestComBtnTouch();
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestLoadTextureBtnTouch();
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestLoadMaterialBtnTouch();
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestChangeMaterialBtnTouch();
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onLevelLoaded();

public:
	void onLevelLoadedDispatch(uint eventId, IDispatchObject* dispObj);
};