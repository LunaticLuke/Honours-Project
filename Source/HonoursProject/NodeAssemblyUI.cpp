// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeAssemblyUI.h"

#include "Components/Image.h"

void UNodeAssemblyUI::SetImage(UClass* ClassOnCollider)
{
	ScreenImage->SetBrushFromTexture(*Images.Find(ClassOnCollider));
}

void UNodeAssemblyUI::ResetImage()
{
	ScreenImage->SetBrushFromTexture(DefaultImage);
}
