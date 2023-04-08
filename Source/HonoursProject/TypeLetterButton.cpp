// Fill out your copyright notice in the Description page of Project Settings.


#include "TypeLetterButton.h"

#include "CreateVariableMachine.h"
#include "Components/TextBlock.h"

UTypeLetterButton::UTypeLetterButton()
{
	OnClicked.AddDynamic(this,&UTypeLetterButton::AddCharacter);
}

void UTypeLetterButton::AddCharacter()
{

if(!MachineRef)
{
	GEngine->AddOnScreenDebugMessage(-1,50.0f,FColor::Red,TEXT("Missing Reference"));
}

	if(LowerCaseCharacterToAdd == "Caps")
	{
		MachineRef->CapsLock();
	}
	else
	{
		if(bLetter)
		{
			if(MachineRef->bChoosingVariableName)
			{
				if(MachineRef->bCapsLock)
				{
					MachineRef->AddToVariableName(UpperCaseCharacterToAdd);
				}
				else
				{
					MachineRef->AddToVariableName(LowerCaseCharacterToAdd);
				}
			}
			else if(MachineRef->bChoosingVariableStartingValue)
			{
				if(MachineRef->bCapsLock)
				{
					MachineRef->AddToVariableStartingValue(UpperCaseCharacterToAdd,false);
				}
				else
				{
					MachineRef->AddToVariableStartingValue(LowerCaseCharacterToAdd,false);
				}
			}
		}
		else
		{
			if(MachineRef->bChoosingVariableStartingValue)
			{
				MachineRef->AddToVariableStartingValue(NumberToAdd,true);
			}
		}
	}
}

void UTypeLetterButton::SetTextComponent(UTextBlock* TextToSet)
{
	TextComponent = TextToSet;
}

void UTypeLetterButton::UpdateText()
{
	if(MachineRef->bCapsLock)
	{
		TextComponent->SetText(FText::FromString(UpperCaseCharacterToAdd));
	}
	else
	{
		TextComponent->SetText(FText::FromString(LowerCaseCharacterToAdd));
	}
}
