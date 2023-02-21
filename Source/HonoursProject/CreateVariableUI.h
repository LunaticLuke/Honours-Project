// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectDataTypeButton.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CreateVariableUI.generated.h"


class UTypeLetterButton;

/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API UCreateVariableUI : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;
	void ShowKeyboard(bool bShow);
	void SetupButtons(ACreateVariableMachine* Machine);


	
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


	TArray<UTypeLetterButton*> KeyboardButtons;

	bool bChoosingVariableName = true;

	bool bChoosingVariableStartingValue = false;
	
	UPROPERTY(meta=(BindWidget))
	UButton* BackspaceKey;
	
	
};
