#pragma once

//https://answers.unrealengine.com/questions/524401/geteditormode-unknown-override-specifier.html
//解决方案
//(1)
//I replaced this line:
//#include "AnimGraphNode_Base.h"
//on this line :
//#include "AnimGraphDefinitions.h"
//(2)
//Hello, in case anyone is still having this issue, I included "Editor/UnrealEd/Public/Editor.h" before AnimGraphNode_Base.h and it worked for me.

// 使用这两行
#include "Editor/UnrealEd/Public/Editor.h"
#include "AnimGraphNode_Base.h"	// UAnimGraphNode_Base
// 不使用这两行
//#include "AnimGraphDefinitions.h"
//#include "Kismet2/BlueprintEditorUtils.h"
//#include "AnimNode_TranslateWith.h"
#include "AnimGraphNode_TranslateWith.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Animation_Node,_Translate_With_Complete_Source_Code_and_Instructions
 */

// error : The dependsOn specifier is deprecated. Please use #include "ClassHeaderFilename.h" instead.
//UCLASS(MinimalAPI, dependson = AnimNode_TranslateWith)
UCLASS()
class UAnimGraphNode_TranslateWith : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	//UPROPERTY(EditAnywhere, Category = SkeletalControl)
	//FAnimNode_TranslateWith Node;

public:
	// UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	// warning C4996: 'UEdGraphNode::GetTooltip': UEdGraphNode::GetTooltip() is deprecated, instead use GetTooltipText(), which returns localized text. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//virtual FString GetTooltip() const override;
	virtual FText GetTooltipText() const override;
	virtual FString GetNodeCategory() const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void CreateOutputPins() override;
	// End of UEdGraphNode interface

protected:
	virtual FText GetControllerDescription() const;
};