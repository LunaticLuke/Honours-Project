// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialUI.h"

#include "Components/Image.h"

void UTutorialUI::NativeConstruct()
{
	Super::NativeConstruct();
	SlideImage->SetBrushFromTexture(DataTypesAndVariablesSlides[currentSlideNumber],false);
}

void UTutorialUI::NextSlide()
{
	currentSlideNumber = FMath::Clamp(currentSlideNumber + 1,0,DataTypesAndVariablesSlides.Num() - 1);
	SlideImage->SetBrushFromTexture(DataTypesAndVariablesSlides[currentSlideNumber],false);
}

void UTutorialUI::PreviousSlide()
{
	currentSlideNumber = FMath::Clamp(currentSlideNumber - 1,0,DataTypesAndVariablesSlides.Num() - 1);
	SlideImage->SetBrushFromTexture(DataTypesAndVariablesSlides[currentSlideNumber],false);
}

int UTutorialUI::GetCurrentSlideNumber()
{
	return currentSlideNumber;
}
