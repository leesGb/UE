// Created by Chance_07 2014

#include "MyProjectEditor.h"
#include "AnimationRuntime.h"
#include "Editor/AnimGraph/Private/AnimGraphPrivatePCH.h"
#include "AnimationGraphSchema.h"
#include "AnimGraphNode_TranslateWith.h"

#define LOCTEXT_NAMESPACE "AnimGraphNode_TranslateWith"

UAnimGraphNode_TranslateWith::UAnimGraphNode_TranslateWith(const FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

//Title Color!
FLinearColor UAnimGraphNode_TranslateWith::GetNodeTitleColor() const
{
	return FLinearColor(0.75f, 0.75f, 0.10f);
}

//Node Category
FString UAnimGraphNode_TranslateWith::GetNodeCategory() const
{
	return FString("Skeletal Controls");
}

FText UAnimGraphNode_TranslateWith::GetControllerDescription() const
{
	return LOCTEXT("TranslateWithNode", "Translate With");
}

//Node Tooltip
//FString UAnimGraphNode_TranslateWith::GetTooltip() const
//{
//	return TEXT("The Translate WIth control allows the Target Bone to follow the Translation of the Source Bone on all Specified Axis");
//}

FText UAnimGraphNode_TranslateWith::GetTooltipText() const
{
	FString tmp = "Template";
	return FText::FromString(tmp);
}

//Node Title(Needs to be updated now since node is much more versatile)
FText UAnimGraphNode_TranslateWith::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("ControllerDescription"), GetControllerDescription());

	if (TitleType == ENodeTitleType::ListView)
	{
		return FText::Format(LOCTEXT("AnimGraphNode_TranslateWith_Title", "{ControllerDescription}"), Args);
	}
	else
	{
		//Args.Add(TEXT("SourceBoneName"), FText::FromName(Node.SourceBone.BoneName));
		//Args.Add(TEXT("TargetBoneName"), FText::FromName(Node.TargetBone.BoneName));
		//return FText::Format(LOCTEXT("AnimGraphNode_TranslateWith_Title", "{ControllerDescription}\nSource Bone: {SourceBoneName}\nTarget Bone: {TargetBoneName}"), Args);

		return FText::Format(LOCTEXT("AnimGraphNode_TranslateWith_Title", "{ControllerDescription}"), Args);
	}
}

//Node Output Pin(Output is in Component Space, Change at own RISK!)
void UAnimGraphNode_TranslateWith::CreateOutputPins()
{
	const UAnimationGraphSchema* Schema = GetDefault<UAnimationGraphSchema>();
	CreatePin(EGPD_Output, Schema->PC_Struct, TEXT(""), FComponentSpacePoseLink::StaticStruct(), /*bIsArray=*/ false, /*bIsReference=*/ false, TEXT("Pose"));
}

#undef LOCTEXT_NAMESPACE