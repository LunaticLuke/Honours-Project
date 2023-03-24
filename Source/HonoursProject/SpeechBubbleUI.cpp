// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeechBubbleUI.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USpeechBubbleUI::SetText(FString TextToSet)
{
	SpeechText->SetText(FText::FromString(TextToSet));
}

void USpeechBubbleUI::ShowUI(bool bShow)
{
	if(!bShow)
	{
		SpeechText->SetText(FText::FromString(""));
		SpeechBubble->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{

		SpeechBubble->SetVisibility(ESlateVisibility::Visible);
	}
	
}
