// Fill out your copyright notice in the Description page of Project Settings.


//#include "UCharacterSlotWidget.h"

#include "CharacterSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "CharacterData.h"



void UCharacterSlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

   /* if (Button_0)
    {
        Button_0->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnCharacter1Selected);
    }

    if (Button_1)
    {
        Button_1->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnCharacter2Selected);
    }

    if (Button_2)
    {
        Button_2->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnCharacter3Selected);
    }*/
}


void UCharacterSlotWidget::SetCharacterData(const FCharacterData& CharacterData)
{
    if (CharacterImage)
    {
        // Set character image here
    }
    if (CharacterName)
    {
        CharacterName->SetText(FText::FromString(CharacterData.Name));
    }

    /*if (InputCharacterName)
    {
        InputCharacterName->Edit
    }*/

    if (CharacterLevel)
    {
        CharacterLevel->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CharacterData.Level)));
    }
}
