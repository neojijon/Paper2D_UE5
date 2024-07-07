// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSlotWidget.generated.h"

struct FCharacterData;


/**
 * 
 */
UCLASS()
class PAPER2D_UE5_API UCharacterSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

    virtual void NativeConstruct() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    TSubclassOf<ACharacter> CharacterClass1;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    TObjectPtr<class UImage> CharacterImage;    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    TObjectPtr<class UTextBlock> CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    TObjectPtr<class UEditableText> InputCharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    TObjectPtr<class UTextBlock> CharacterLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    TObjectPtr<class UEditableText> InputCharacterLevel;

   
    

    void SetCharacterData(const FCharacterData& CharacterData);
	
};
