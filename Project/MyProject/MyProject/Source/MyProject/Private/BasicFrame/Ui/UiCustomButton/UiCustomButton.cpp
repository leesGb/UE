#include "MyProject.h"
#include "UiCustomButton.h"

void SUiCustomButton::Construct(const FArguments& InArgs)
{
	//The button!
	SAssignNew(RefreshButton, SButton)
		.ButtonStyle(FCoreStyle::Get(), "NoBorder")
		.OnClicked(this, &SUiCustomButton::RefreshButtonPressed)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.ForegroundColor(FSlateColor::UseForeground())
		[
			//Colored Background
			SNew(SBorder)
			.Padding(FMargin(3))

		//~~~ Rainbow Image for Button!!! ~~~
		.BorderImage(FCoreStyle::Get().GetBrush("ColorSpectrum.Spectrum"))
		[
			//Button Text!! AssignNew so can change color later
			SAssignNew(RefreshButtonText, STextBlock)
			//.Text(FString("Refresh (F5) "))
		.Text(FText::FromString("Refresh (F5) "))
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 16))
		.ColorAndOpacity(FLinearColor(1, 0, 1, 1))
		.HighlightColor(FLinearColor(1, 1, 0, 1))
		.ShadowColorAndOpacity(FLinearColor::Black)
		.ShadowOffset(FIntPoint(1, -1))
		]
		];

	//Resizes the image
	SNew(SBox)
		.WidthOverride(64)
		.HeightOverride(64)
		[
			//~~~ Clear Button / Trash Can ~~~
			SAssignNew(ClearTileButton, SButton)
			.ButtonStyle(FCoreStyle::Get(), "NoBorder")
		.OnClicked(this, &SUiCustomButton::ClearButtonPressed)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.ForegroundColor(FSlateColor::UseForeground())
		[
			//Button Content Image
			TSharedRef<SWidget>(SNew(SImage).Image(
			FCoreStyle::Get().GetBrush("TrashCan")
				))
		]
		];
}

void SUiCustomButton::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	// Call parent implementation
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);


	//~~~~~~~~~~~~
	// Button Hovering
	//~~~~~~~~~~~~
	if (RefreshButtonText->IsHovered())
	{
		// TODO:
		//SetRainbowGlowColor();
		//RefreshButtonText->SetForegroundColor(RainbowGlowingColor);
		RefreshButtonText->SetColorAndOpacity(FLinearColor(1, 0, 1, 1));
	}
	else
	{
		//RefreshButtonText->SetForegroundColor(FLinearColor(1, 0, 1, 1));
		RefreshButtonText->SetColorAndOpacity(FLinearColor(1, 0, 1, 1));
	}
}

void SUiCustomButton::SetCursor()
{
	//Set Cursors
	ClearTileButton->SetCursor(EMouseCursor::SlashedCircle);
	RefreshButton->SetCursor(EMouseCursor::Hand);
}

void SUiCustomButton::SetToolTip()
{
	ClearTileButton->SetToolTip(
		SNew(SToolTip)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("FileTree", "Clear", "Clear any currently Loaded Preview Tile!  -Rama"))
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 12))
		.ColorAndOpacity(FLinearColor(1, 0, 1, 1))
		.HighlightColor(FLinearColor(1, 1, 0, 1))
		.ShadowColorAndOpacity(FLinearColor::Black)
		.ShadowOffset(FIntPoint(-2, 2))
		]
	);

	RefreshButton->SetToolTip(
		SNew(SToolTip)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("FileTree", "Refresh", "Refresh Directory and File Listing, updating to hard drive contents! -Rama"))
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 12))
		.ColorAndOpacity(FLinearColor(1, 0, 1, 1))
		.HighlightColor(FLinearColor(1, 1, 0, 1))
		.ShadowColorAndOpacity(FLinearColor::Black)
		.ShadowOffset(FIntPoint(-2, 2))
		]
	);
}

FReply SUiCustomButton::RefreshButtonPressed()
{
	return FReply::Handled();
}

FReply SUiCustomButton::ClearButtonPressed()
{
	return FReply::Handled();
}