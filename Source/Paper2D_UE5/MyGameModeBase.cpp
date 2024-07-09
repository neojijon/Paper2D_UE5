// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPaperCharacter_ZD.h"
#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"
#include "CharacterSelectWidget.h"


AMyGameModeBase::AMyGameModeBase()
{
	// ��������� Ŭ������ ����Ʈ Pawn Ŭ������ �����ϴ� ���
		
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Paper2D/BP_Character"));	
		
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/

		
	/*static ConstructorHelpers::FClassFinder<APlayerController> ControllClass(TEXT("/Game/Paper2D/BP_MyPlayerController"));

	if (ControllClass.Class != nullptr)
	{
		PlayerControllerClass = ControllClass.Class;
	}*/

	//�Ϲ� C++ Ŭ������  �����ϴ� ���
	//DefaultPawnClass = AMyPaperCharacter::StaticClass();
    //DefaultPawnClass = PlayerPawnBPClass.Class;
    // 
    //PlayerControllerClass = AMyPlayerController::StaticClass();

    //DefaultPawnClass = SelectedCharacterClass;

    
    SelectedCharacterClass = DefaultPawnClass;
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// �ʱ� ĳ���� ���� ����
	if (SelectedCharacterClass)
	{

		//DefaultPawnClass = SelectedCharacterClass;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(GetWorld()->SpawnActor<AMyPaperCharacter_ZD>(SelectedCharacterClass));
	}

	InitializeCharacterControllerMap();

}

void AMyGameModeBase::SetPlayerCharacter(TSubclassOf<ACharacter> NewCharacterClass)
{
    //DefaultPawnClass = NewCharacterClass;
	SelectedCharacterClass = NewCharacterClass;

    SpawnSelectedCharacter();
}

void AMyGameModeBase::SpawnSelectedCharacter()
{
    if (SelectedCharacterClass)
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PlayerController)
        {
            //���� ������Ʈ ������
            RemoveDefaultPawn();

            FVector SpawnLocation;
            FRotator SpawnRotation;

            if (SpawnPoint)
            {
                SpawnLocation = SpawnPoint->GetActorLocation();
                SpawnRotation = SpawnPoint->GetActorRotation();
            }
            else
            {
                // �⺻ ���� ��ġ ����
                SpawnLocation = FVector(0.f, 0.f, 300.f);
                SpawnRotation = FRotator(0.f, 0.f, 0.f);
            }

            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            ACharacter* NewCharacter = GetWorld()->SpawnActor<ACharacter>(SelectedCharacterClass, SpawnLocation, SpawnRotation, SpawnParams);
            if (NewCharacter)
            {
                PlayerController->Possess(NewCharacter);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to spawn character at location: %s"), *SpawnLocation.ToString());
            }
        }
    }   
}


void AMyGameModeBase::RemoveDefaultPawn()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController && PlayerController->GetPawn())
    {
        PlayerController->GetPawn()->Destroy();
    }
}



//���� �ɸ��� ��Ʈ�ѷ��� �ٸ���
void AMyGameModeBase::SetPlayerControllerForCharacter()
{
    APlayerController* CurrentController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!CurrentController || !CurrentController->GetPawn())
    {
        return;
    }

    TSubclassOf<APlayerController>* ControllerClass = CharacterControllerMap.Find(CurrentController->GetPawn()->GetClass());
    if (ControllerClass && *ControllerClass)
    {
        CurrentController->UnPossess();
        APlayerController* NewController = GetWorld()->SpawnActor<APlayerController>(*ControllerClass);
        NewController->Possess(CurrentController->GetPawn());
        UGameplayStatics::GetPlayerController(GetWorld(), 0)->UnPossess();
        UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(NewController->GetPawn());
    }
}

void AMyGameModeBase::InitializeCharacterControllerMap()
{
    if (CharacterControllerMap.IsEmpty()) return;


    // �� �ʱ�ȭ
    //CharacterControllerMap.Add(AWizardCharacter::StaticClass(), AWizardPlayerController::StaticClass());
    //CharacterControllerMap.Add(AWizardCharacter::StaticClass(), AWizardPlayerController::StaticClass());
    //CharacterControllerMap.Add(AWizardCharacter::StaticClass(), AWizardPlayerController::StaticClass());
}
