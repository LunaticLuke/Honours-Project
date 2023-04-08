// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialUI.generated.h"

enum class ESlideTopic;
class UImage;
class UButton;
/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API UTutorialUI : public UUserWidget
{
	GENERATED_BODY()


protected:

	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UButton* NextSlideButton;
	UPROPERTY(meta=(BindWidget))
	UButton* PreviousSlideButton;
	UPROPERTY(meta=(BindWidget))
	UButton* DataTypesButton;
	UPROPERTY(meta=(BindWidget))
	UButton* ConditionalsButton;
	UPROPERTY(meta=(BindWidget))
	UButton* WhileLoopsButton;
	UPROPERTY(meta=(BindWidget))
	UButton* ForLoopsButton;
	UPROPERTY(meta=(BindWidget))
	UImage* SlideImage;
	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> DataTypesAndVariablesSlides;

	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> ConditionalsSlides;

	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> ForLoopSlides;
	
	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> WhileLoopSlides;
	
	UPROPERTY(EditAnywhere)
	int currentSlideNumber=  0;

	
	UFUNCTION()
	void NextSlide();
	
	UFUNCTION()
	void PreviousSlide();
	
	bool bQuizSlides = false;

	ESlideTopic CurrentTopic;

	int CurrentQuestionNumber = 0;
	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> QuizSlides;
	
	UFUNCTION()
	void ChooseDataTypes();
	UFUNCTION()
	void ChooseConditionals();
	UFUNCTION()
	void ChooseForLoops();
	UFUNCTION()
	void ChooseWhileLoops();
public:
	int GetCurrentSlideNumber();

	void SetQuiz(bool bIsQuiz);

	void SetQuizNumber(int QuestionNumber);

	void ShowImage(bool bShow);

	ESlideTopic GetCurrentSlideTopic();

	void UnlockTopic(ESlideTopic TopicToUnlock);
};
