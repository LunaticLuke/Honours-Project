// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectDataTypeButton.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CreateVariableUI.generated.h"


class ACreateVariableMachine;
class UTextBlock;
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
	void ShowNumbers(bool bShow);
	void ShowBools(bool bShow);
	void SetupButtons(ACreateVariableMachine* Machine);

	void UpdateText(FString DataType, FString VariableName, FString VariableValue);
	UFUNCTION()
	void Space();
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
	UFUNCTION()
	void SelectName();
	UFUNCTION()
	void SelectStartingValue();
	UFUNCTION()
	void SelectTrue();
	UFUNCTION()
	void SelectFalse();
	
	TArray<UTypeLetterButton*> KeyboardButtons;
	TArray<UTypeLetterButton*> NumpadButtons;
	UPROPERTY(meta=(BindWidget))
	UButton* SpacebarKey;
	
	UPROPERTY(meta=(BindWidget))
	UButton* BackSpaceNumKey;

	
	UPROPERTY(meta=(BindWidget))
	UButton* BackspaceKey;
	UPROPERTY(meta=(BindWidget))
	UButton* TrueButton;
	UPROPERTY(meta=(BindWidget))
	UButton* FalseButton;
	UPROPERTY(meta=(BindWidget))
	UButton* SelectNameButton;
	UPROPERTY(meta=(BindWidget))
	UButton* SelectVariableValueButton;
	UPROPERTY(meta=(BindWidget))
	UButton* CreateVariableButton;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* VariableTypeText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* VariableNameText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* VariableStartingValueText;

	

protected:
	ACreateVariableMachine* VariableMachine;
	UFUNCTION()
	void BackSpace();
	UFUNCTION()
	void CreateVariable();
};


