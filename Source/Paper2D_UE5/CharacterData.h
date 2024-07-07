// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CharacterData.generated.h"


USTRUCT(BlueprintType)
struct FCharacterData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    UTexture2D* CharacterImage;
};