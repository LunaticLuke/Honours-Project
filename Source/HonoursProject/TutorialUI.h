// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialUI.generated.h"

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
	UImage* SlideImage;
	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> DataTypesAndVariablesSlides;
	UPROPERTY(EditAnywhere)
	int currentSlideNumber=  0;


	UFUNCTION()
	void NextSlide();
	
	UFUNCTION()
	void PreviousSlide();
	
	bool bQuizSlides = false;


	int CurrentQuestionNumber = 0;
	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> QuizSlides;
public:
	int GetCurrentSlideNumber();

	void SetQuiz(bool bIsQuiz);

	void SetQuizNumber(int QuestionNumber);

	void ShowImage(bool bShow);
};
