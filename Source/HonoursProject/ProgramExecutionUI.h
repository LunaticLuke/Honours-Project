// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ProgramExecutionUI.generated.h"

class AProgramManager;
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

	AProgramManager* Manager;

	UButton* ClearLogButton;
public:
	void NativeConstruct() override;
	
	void DisplayProgram(class AFunctionNode* VariableToAdd);

	UFUNCTION()
	void ClearLog();

	void SetManager(AProgramManager* ProgramToSet);
	
};
