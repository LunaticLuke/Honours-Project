// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "VariableListUI.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API UVariableListUI : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta=(BindWidget))
	UTextBlock* VariableText;
	FString VariableListString = "";
public:
	void DisplayVariables(class AVariableNodeActor* VariableToAdd);

	void ClearVariableLog();
};
