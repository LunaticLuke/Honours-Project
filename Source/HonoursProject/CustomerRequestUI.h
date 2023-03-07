// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomerRequestUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API UCustomerRequestUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UTextBlock* CustomerRequestText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CustomerFeedbackText;

public:
	void SetCustomerRequest(FString StringToSet);

	void SetCustomerFeedback(FString StringToSet);
};
