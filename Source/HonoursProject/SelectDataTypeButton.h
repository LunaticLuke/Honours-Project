// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumManager.h"
#include "Components/Button.h"
#include "SelectDataTypeButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);
/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API USelectDataTypeButton : public UButton
{
	GENERATED_BODY()

public:
	USelectDataTypeButton();
	class ACreateVariableMachine* MachineRef;

	FClickDelegate click;
protected:
	UPROPERTY(EditAnywhere)
	NodeDataTypes TypeToSelect = NodeDataTypes::Unassigned;
	UFUNCTION()
	void ChooseDataType();
};
