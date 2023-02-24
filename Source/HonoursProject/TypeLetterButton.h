// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "TypeLetterButton.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API UTypeLetterButton : public UButton
{
	GENERATED_BODY()

	UTypeLetterButton();
public:
	class ACreateVariableMachine* MachineRef;
	UPROPERTY(EditAnywhere)
	bool bLetter = true;
	UFUNCTION()
	void AddCharacter();
protected:
	UPROPERTY(EditAnywhere)
	FString LowerCaseCharacterToAdd;
	UPROPERTY(EditAnywhere)
	FString UpperCaseCharacterToAdd;
	UPROPERTY(EditAnywhere)
	FString NumberToAdd;
};
