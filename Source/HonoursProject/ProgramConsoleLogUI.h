// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ProgramConsoleLogUI.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API UProgramConsoleLogUI : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LogTextBlock;
	FString ProgramLogString;

public:
	void AddOutput(FString LineToAdd);

	void ClearLog();
};
