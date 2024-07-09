#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MyGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FMyCharacterData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    FString CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    UTexture2D* RoleIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    UTexture2D* PicPortrait;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    UTexture2D* PicFull;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    int32 Affinity01;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    int32 Affinity02;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    int32 XP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    int32 Money;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    bool AutoMove;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    float AutoMoveSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    float HealthRegenAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    float HealthRegenRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    FString Taunts;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    FString TauntString;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    FColor Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    int32 Ability01;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    int32 Ability02;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    int32 Ability03;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    int32 Ability04;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Data")
    int32 Ability05;
};

UCLASS()
class PAPER2D_UE5_API UMyGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Character Data")
    bool GetCharacterData(FName RowName, FMyCharacterData& OutRow);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Data")
    TObjectPtr<UDataTable> MyCharacterDataTable;
};
