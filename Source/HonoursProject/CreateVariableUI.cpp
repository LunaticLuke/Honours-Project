// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateVariableUI.h"

#include "TypeLetterButton.h"


void UCreateVariableUI::NativeConstruct()
{
	Super::NativeConstruct();

	const UClass* Class = GetClass();
	FProperty* Property = Class->PropertyLink;

	while (Property != nullptr)
	{
		if(Property->GetClass() == FObjectProperty::StaticClass())
		{
			const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property);
			UObject* Object = ObjectProperty->GetObjectPropertyValue_InContainer(this);

			if(ObjectProperty->PropertyClass == UTypeLetterButton::StaticClass())
			{
				if(UTypeLetterButton* Button = Cast<UTypeLetterButton>(Object))
				{
					KeyboardButtons.Push(Button);
				}
			}
		}
		Property = Property->PropertyLinkNext;
	}
	for(int i = 0; i < KeyboardButtons.Num();i++)
	{
		KeyboardButtons[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCreateVariableUI::SetupButtons(ACreateVariableMachine* Machine)
{
	SelectString->MachineRef = Machine;
	SelectBool->MachineRef = Machine;
	SelectInt->MachineRef = Machine;
	SelectFloat->MachineRef = Machine;
	SelectChar->MachineRef = Machine;

	for(int i = 0; i < KeyboardButtons.Num();i++)
	{
		KeyboardButtons[i]->MachineRef = Machine;
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
	}
	else
	{
		BackspaceKey->SetVisibility(ESlateVisibility::Hidden);
	}
}


