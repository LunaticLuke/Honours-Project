// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectDataTypeButton.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CreateVariableUI.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API UCreateVariableUI : public UUserWidget
{
	GENERATED_BODY()

public:
	
	
	
	UPROPERTY(meta=(BindWidget))
	USelectDataTypeButton* SelectBool;
	UPROPERTY(meta=(BindWidget))
	USelectDataTypeButton* SelectString;
	UPROPERTY(meta=(BindWidget))
	USelectDataTypeButton* SelectInt;
	UPROPERTY(meta=(BindWidget))
	USelectDataTypeButton* SelectFloat;
	UPROPERTY(meta=(BindWidget))
	USelectDataTypeButton* SelectChar;

	void SetupButtons(ACreateVariableMachine* Machine);
};
