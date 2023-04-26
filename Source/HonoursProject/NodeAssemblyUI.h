// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NodeAssemblyUI.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API UNodeAssemblyUI : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TMap<UClass*, UTexture2D*> Images;
	
	UPROPERTY(meta=(BindWidget))
	UImage* ScreenImage;
	UPROPERTY(EditAnywhere)
	UTexture2D* DefaultImage;

public:
	
	UFUNCTION()
	void SetImage(UClass* ClassOnCollider);
	UFUNCTION()
	void ResetImage();
};
