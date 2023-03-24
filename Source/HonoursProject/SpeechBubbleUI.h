// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpeechBubbleUI.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API USpeechBubbleUI : public UUserWidget
{
	GENERATED_BODY()


public:
	void SetText(FString TextToSet);

	void ShowUI(bool bShow);

protected:
	
	UPROPERTY(meta=(BindWidget))
	UImage* SpeechBubble;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SpeechText;
};
