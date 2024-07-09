#include "MyGameInstance.h"

bool UMyGameInstance::GetCharacterData(FName RowName, FMyCharacterData& OutRow)
{
    if (!MyCharacterDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("Character Data Table is not set"));
        return false;
    }

    FMyCharacterData* Row = MyCharacterDataTable->FindRow<FMyCharacterData>(RowName, TEXT(""));

    if (!Row)
    {
        UE_LOG(LogTemp, Warning, TEXT("Row not found in Data Table"));
        return false;
    }

    OutRow = *Row;
    return true;
}
