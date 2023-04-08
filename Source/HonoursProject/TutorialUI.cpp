// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialUI.h"

#include "TutorialManager.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UTutorialUI::NativeConstruct()
{
	Super::NativeConstruct();
	NextSlideButton->OnClicked.AddDynamic(this,&UTutorialUI::NextSlide);
	PreviousSlideButton->OnClicked.AddDynamic(this,&UTutorialUI::PreviousSlide);
	DataTypesButton->OnClicked.AddDynamic(this,&UTutorialUI::ChooseDataTypes);
	ConditionalsButton->OnClicked.AddDynamic(this,&UTutorialUI::ChooseConditionals);
	ForLoopsButton->OnClicked.AddDynamic(this,&UTutorialUI::ChooseForLoops);
	WhileLoopsButton->OnClicked.AddDynamic(this,&UTutorialUI::ChooseWhileLoops);
	CurrentTopic = ESlideTopic::DataTypes_Variables;
	
	ConditionalsButton->SetIsEnabled(false);
	ForLoopsButton->SetIsEnabled(false);
	WhileLoopsButton->SetIsEnabled(false);

	if(bQuizSlides)
	{
		DataTypesButton->SetVisibility(ESlateVisibility::Hidden);
		ForLoopsButton->SetVisibility(ESlateVisibility::Hidden);
		WhileLoopsButton->SetVisibility(ESlateVisibility::Hidden);
		ConditionalsButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTutorialUI::NextSlide()
{
	switch (CurrentTopic)
	{
	case ESlideTopic::DataTypes_Variables:
		currentSlideNumber = FMath::Clamp(currentSlideNumber + 1,0,DataTypesAndVariablesSlides.Num() - 1);
		SlideImage->SetBrushFromTexture(DataTypesAndVariablesSlides[currentSlideNumber],false);
		break;
	case ESlideTopic::For_Loops:
		currentSlideNumber = FMath::Clamp(currentSlideNumber + 1,0,ForLoopSlides.Num() - 1);
		SlideImage->SetBrushFromTexture(ForLoopSlides[currentSlideNumber],false);
		break;
	case ESlideTopic::Conditionals:
		currentSlideNumber = FMath::Clamp(currentSlideNumber + 1,0,ConditionalsSlides.Num() - 1);
		SlideImage->SetBrushFromTexture(ConditionalsSlides[currentSlideNumber],false);
		break;
	case ESlideTopic::While_Loops:
		currentSlideNumber = FMath::Clamp(currentSlideNumber + 1,0,WhileLoopSlides.Num() - 1);
		SlideImage->SetBrushFromTexture(WhileLoopSlides[currentSlideNumber],false);
		break;
	default: ;
	}
}

void UTutorialUI::PreviousSlide()
{
	switch (CurrentTopic)
	{
	case ESlideTopic::DataTypes_Variables:
		currentSlideNumber = FMath::Clamp(currentSlideNumber - 1,0,DataTypesAndVariablesSlides.Num() - 1);
		SlideImage->SetBrushFromTexture(DataTypesAndVariablesSlides[currentSlideNumber],false);
		break;
	case ESlideTopic::For_Loops:
		currentSlideNumber = FMath::Clamp(currentSlideNumber - 1,0,ForLoopSlides.Num() - 1);
		SlideImage->SetBrushFromTexture(ForLoopSlides[currentSlideNumber],false);
		break;
	case ESlideTopic::Conditionals:
		currentSlideNumber = FMath::Clamp(currentSlideNumber - 1,0,ConditionalsSlides.Num() - 1);
		SlideImage->SetBrushFromTexture(ConditionalsSlides[currentSlideNumber],false);
		break;
	case ESlideTopic::While_Loops:
		currentSlideNumber = FMath::Clamp(currentSlideNumber - 1,0,WhileLoopSlides.Num() - 1);
		SlideImage->SetBrushFromTexture(WhileLoopSlides[currentSlideNumber],false);
		break;
	default: ;
	}
}

void UTutorialUI::ChooseDataTypes()
{
	currentSlideNumber = 0;
	CurrentTopic = ESlideTopic::DataTypes_Variables;
	SlideImage->SetBrushFromTexture(DataTypesAndVariablesSlides[currentSlideNumber],false);
}

void UTutorialUI::ChooseConditionals()
{
	currentSlideNumber = 0;
	CurrentTopic = ESlideTopic::Conditionals;
	SlideImage->SetBrushFromTexture(ConditionalsSlides[currentSlideNumber],false);
}

void UTutorialUI::ChooseForLoops()
{
	currentSlideNumber = 0;
	CurrentTopic = ESlideTopic::For_Loops;
	SlideImage->SetBrushFromTexture(ForLoopSlides[currentSlideNumber],false);
}

void UTutorialUI::ChooseWhileLoops()
{
	currentSlideNumber = 0;
	CurrentTopic = ESlideTopic::While_Loops;
	SlideImage->SetBrushFromTexture(WhileLoopSlides[currentSlideNumber],false);
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

ESlideTopic UTutorialUI::GetCurrentSlideTopic()
{
	return CurrentTopic;
}

void UTutorialUI::UnlockTopic(ESlideTopic TopicToUnlock)
{
	switch (TopicToUnlock)
	{
	case ESlideTopic::DataTypes_Variables:
		CurrentTopic = ESlideTopic::DataTypes_Variables;
		DataTypesButton->SetIsEnabled(true);
		ChooseDataTypes();
		break;
	case ESlideTopic::For_Loops:
		CurrentTopic = ESlideTopic::For_Loops;
		ForLoopsButton->SetIsEnabled(true);
		ChooseForLoops();
		break;
	case ESlideTopic::Conditionals:
		CurrentTopic = ESlideTopic::Conditionals;
		ConditionalsButton->SetIsEnabled(true);
		ChooseConditionals();
		break;
	case ESlideTopic::While_Loops:
		CurrentTopic = ESlideTopic::While_Loops;
		WhileLoopsButton->SetIsEnabled(true);
		ChooseWhileLoops();
		break;
	default: ;
	}
}

