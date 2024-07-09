// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPaperCharacter.h"
#include "MyPaperCharacter_ZD.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#include "CharacterSelectWidget.h"


AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(IMC_SideScroller.Get(), 1);
    }


    if (CharacterSelectWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("CharacterSelectWidgetClass"));

        CharacterSelectWidgetInstance = CreateWidget<UUserWidget>(this, CharacterSelectWidgetClass);
        if (CharacterSelectWidgetInstance)
        {
            UE_LOG(LogTemp, Warning, TEXT("AddToViewport"));

            CharacterSelectWidgetInstance->AddToViewport();
            CharacterSelectWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        }
    }

}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(IA_Move.Get(), ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
        EnhancedInputComponent->BindAction(IA_Walk.Get(), ETriggerEvent::Triggered, this, &AMyPlayerController::Walk);        
        EnhancedInputComponent->BindAction(IA_Attack.Get(), ETriggerEvent::Triggered, this, &AMyPlayerController::Attack);
        //EnhancedInputComponent->BindAction(IA_Jump.Get(), ETriggerEvent::Triggered, this, &AMyPlayerController::Jump);


        //�ɸ��� ����â ���
        EnhancedInputComponent->BindAction(IA_ToggleCharacterSelect.Get(), ETriggerEvent::Triggered, this, &AMyPlayerController::ToggleCharacterSelectWidget);

    }
   /* else
    {
        InputComponent->BindAction("ToggleCharacterSelect", IE_Pressed, this, &AMyPlayerController::ToggleCharacterSelectWidget);
    }*/
    

    
}


void AMyPlayerController::ToggleCharacterSelectWidget()
{

    if (CharacterSelectWidgetInstance)
    {
        if (CharacterSelectWidgetInstance->IsVisible())
        {
            CharacterSelectWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
            ShowMouseCursor(false);
        }
        else
        {
            CharacterSelectWidgetInstance->SetVisibility(ESlateVisibility::Visible);
            ShowMouseCursor(true);
        }
    }
}

void AMyPlayerController::ShowMouseCursor(bool bShow)
{
    bShowMouseCursor = bShow;
    if (bShow)
    {
        SetInputMode(FInputModeUIOnly());
    }
    else
    {
        SetInputMode(FInputModeGameOnly());
    }
}



void AMyPlayerController::Move(const FInputActionValue& Value)
{
   
    //if (APawn* ControlledPawn = GetPawn())
    //{
    //    FVector2D MovementVector = Value.Get<FVector2D>();
    //    
    //    if (AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(ControlledPawn))
    //    {
    //        MyCharacter->Move(MovementVector.X);
    //    }
    //    else if (AMyPaperCharacter_ZD* MyCharacter_ZD = Cast<AMyPaperCharacter_ZD>(ControlledPawn))
    //    {
    //        MyCharacter_ZD->Move(MovementVector.X);
    //    }
    //}
}

void AMyPlayerController::Walk(const FInputActionValue& Value)
{
    /*if (APawn* ControlledPawn = GetPawn())
    {
        if (AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(ControlledPawn))
        {
            MyCharacter->Walk(Value);
        }
    }*/

    UE_LOG(LogTemp, Warning, TEXT("Walk"));
}

//
//void AMyPlayerController::Jump(const FInputActionValue& Value)
//{
//    if (APawn* ControlledPawn = GetPawn())
//    {
//        if (AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(ControlledPawn))
//        {
//            MyCharacter->Jump();
//        }
//    }
//}


void AMyPlayerController::Attack(const FInputActionValue& Value)
{
   /* if (APawn* ControlledPawn = GetPawn())
    {
        if (AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(ControlledPawn))
        {
            MyCharacter->Attack();            
        }
        else if (AMyPaperCharacter_ZD* MyCharacter_ZD = Cast<AMyPaperCharacter_ZD>(ControlledPawn))
        {
            MyCharacter_ZD->Attack();
        }
    }*/
}

