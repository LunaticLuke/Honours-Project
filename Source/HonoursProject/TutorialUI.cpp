// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialUI.h"

#include "Components/Button.h"
#include "Components/Image.h"

void UTutorialUI::NativeConstruct()
{
	Super::NativeConstruct();
	NextSlideButton->OnClicked.AddDynamic(this,&UTutorialUI::NextSlide);
	PreviousSlideButton->OnClicked.AddDynamic(this,&UTutorialUI::PreviousSlide);
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

void UTutorialUI::SetQuiz(bool bIsQuiz)
{
	bQuizSlides = bIsQuiz;
	if(bQuizSlides)
	{
		NextSlideButton->SetVisibility(ESlateVisibility::Hidden);
		PreviousSlideButton->SetVisibility(ESlateVisibility::Hidden);
		SlideImage->SetBrushFromTexture(QuizSlides[CurrentQuestionNumber]);
		ShowImage(false);
	}
	else
	{
		SlideImage->SetBrushFromTexture(DataTypesAndVariablesSlides[currentSlideNumber],false);
	}
}

void UTutorialUI::SetQuizNumber(int QuestionNumber)
{
	CurrentQuestionNumber = QuestionNumber;
	SlideImage->SetBrushFromTexture(QuizSlides[CurrentQuestionNumber]);
}

void UTutorialUI::ShowImage(bool bShow)
{
	if(bShow)
	{
		SlideImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SlideImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
