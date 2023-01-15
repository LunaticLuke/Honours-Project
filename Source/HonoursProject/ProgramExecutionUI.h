// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ProgramExecutionUI.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API UProgramExecutionUI : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ExecutionTextBlock;
	FString ProgramExecutionString;

public:
	void DisplayProgram(class AFunctionNode* VariableToAdd);

	void ClearLog();
	
};
