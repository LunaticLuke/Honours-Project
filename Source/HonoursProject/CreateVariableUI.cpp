// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateVariableUI.h"

#include "CreateVariableMachine.h"
#include "TypeLetterButton.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"


void UCreateVariableUI::NativeConstruct()
{
	Super::NativeConstruct();

	const UClass* Class = GetClass();
	FProperty* Property = Class->PropertyLink;

	TArray<UWidget*> Children;
	WidgetTree->GetAllWidgets(Children);
	UE_LOG(LogTemp, Warning, TEXT("Children Size: %d"), Children.Num());
	for(auto Child: Children)
	{
		if(UTypeLetterButton* Button = Cast<UTypeLetterButton>(Child))
		{
			Button->MachineRef = VariableMachine;
			if(Button->bLetter)
			{
				KeyboardButtons.Push(Button);
			}
			else
			{
				NumpadButtons.Push(Button);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("KeyboardButtons Size: %d"), KeyboardButtons.Num());
	UE_LOG(LogTemp, Warning, TEXT("NumberButtons Size: %d"), NumpadButtons.Num());
	
	SelectName();
	TrueButton->OnClicked.AddDynamic(this,&UCreateVariableUI::SelectTrue);
	FalseButton->OnClicked.AddDynamic(this,&UCreateVariableUI::SelectFalse);
	BackspaceKey->OnClicked.AddDynamic(this,&UCreateVariableUI::BackSpace);
	BackSpaceNumKey->OnClicked.AddDynamic(this,&UCreateVariableUI::BackSpace);
	SelectNameButton->OnClicked.AddDynamic(this,&UCreateVariableUI::SelectName);
	SelectVariableValueButton->OnClicked.AddDynamic(this,&UCreateVariableUI::SelectStartingValue);
	CreateVariableButton->OnClicked.AddDynamic(this,&UCreateVariableUI::CreateVariable);
	SpacebarKey->OnClicked.AddDynamic(this,&UCreateVariableUI::Space);
}

void UCreateVariableUI::SetupButtons(ACreateVariableMachine* Machine)
{
	SelectString->MachineRef = Machine;
	SelectBool->MachineRef = Machine;
	SelectInt->MachineRef = Machine;
	SelectFloat->MachineRef = Machine;
	SelectChar->MachineRef = Machine;

	VariableMachine = Machine;
	
	for(int i = 0; i < KeyboardButtons.Num();i++)
	{
		KeyboardButtons[i]->MachineRef = Machine;
	}

	for(int i = 0; i < NumpadButtons.Num();i++)
	{
		NumpadButtons[i]->MachineRef = Machine;
	}
	
}

void UCreateVariableUI::UpdateText(FString DataType, FString VariableName, FString VariableValue)
{
	if(DataType == "No Data Type")
	{
		VariableTypeText->SetText(FText::FromString(""));
	}
	else
	{
	VariableTypeText->SetText(FText::FromString(DataType));
	}
	VariableNameText->SetText(FText::FromString(VariableName));
	VariableStartingValueText->SetText(FText::FromString(VariableValue));
}

void UCreateVariableUI::Space()
{
	if(VariableMachine->bChoosingVariableStartingValue)
	{
		VariableMachine->AddToVariableStartingValue(" ",false);
	}
}

void UCreateVariableUI::SelectName()
{
		VariableMachine->bChoosingVariableName = true;
		VariableMachine->bChoosingVariableStartingValue = false;
	if(VariableMachine->GetCurrentDataType() != NodeDataTypes::Unassigned)
	{
		ShowKeyboard(true);
		ShowNumbers(false);
		ShowBools(false);
	}
	else
	{
		ShowKeyboard(false);
		ShowNumbers(false);
		ShowBools(false);
	}
}

void UCreateVariableUI::SelectStartingValue()
{

	VariableMachine->bChoosingVariableName = false;
	VariableMachine->bChoosingVariableStartingValue = true;

	if(VariableMachine->GetCurrentDataType() == NodeDataTypes::Unassigned)
	{
		ShowKeyboard(false);
		ShowNumbers(false);
		ShowBools(false);
	}else if(VariableMachine->GetCurrentDataType() == NodeDataTypes::Int || VariableMachine->GetCurrentDataType() == NodeDataTypes::Float)
	{
		ShowNumbers(true);
		ShowKeyboard(false);
		ShowBools(false);
	}else if(VariableMachine->GetCurrentDataType() == NodeDataTypes::Bool)
	{
		ShowNumbers(false);
		ShowKeyboard(false);
		ShowBools(true);
	}
	else if(VariableMachine->GetCurrentDataType() == NodeDataTypes::Char || VariableMachine->GetCurrentDataType() == NodeDataTypes::String)
	{
		ShowNumbers(false);
		ShowKeyboard(true);
		ShowBools(false);
	}
}

void UCreateVariableUI::SelectTrue()
{
	VariableMachine->AddToVariableStartingValue("true",false);
}

void UCreateVariableUI::SelectFalse()
{
	VariableMachine->AddToVariableStartingValue("false",false);
}

void UCreateVariableUI::BackSpace()
{
	VariableMachine->Backspace();
}

void UCreateVariableUI::CreateVariable()
{
	VariableMachine->CreateVariable();
}

void UCreateVariableUI::ShowBools(bool bShow)
{
	if(bShow)
	{
		TrueButton->SetVisibility(ESlateVisibility::Visible);
		FalseButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TrueButton->SetVisibility(ESlateVisibility::Hidden);
		FalseButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCreateVariableUI::ShowKeyboard(bool bShow)
{
	for(int i = 0; i < KeyboardButtons.Num(); i++)
	{
		if(bShow)
		{
			KeyboardButtons[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			KeyboardButtons[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if(bShow)
	{
		BackspaceKey->SetVisibility(ESlateVisibility::Visible);
		SpacebarKey->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BackspaceKey->SetVisibility(ESlateVisibility::Hidden);
		SpacebarKey->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCreateVariableUI::ShowNumbers(bool bShow)
{
	for(int i = 0; i < NumpadButtons.Num();i++)
	{
		if(bShow)
		{
			NumpadButtons[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			NumpadButtons[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if(bShow)
	{
		BackSpaceNumKey->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BackSpaceNumKey->SetVisibility(ESlateVisibility::Hidden);

	}
}


