// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerRequestUI.h"

#include "Components/TextBlock.h"

void UCustomerRequestUI::SetCustomerRequest(FString StringToSet)
{
	CustomerRequestText->SetText(FText::FromString(StringToSet));
}

void UCustomerRequestUI::SetCustomerFeedback(FString StringToSet)
{
	CustomerFeedbackText->SetText(FText::FromString(StringToSet));
}
