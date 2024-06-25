// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPaperCharacter.h"
#include "UObject/ConstructorHelpers.h"




AMyPlayerController::AMyPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;

    //인풋관련 초기 세팅
    // Input Actions
    static ConstructorHelpers::FObjectFinder<UInputAction> IA_Move_OBJ(TEXT("/Game/Paper2D/Input/Actions/IA_Move"));
    IA_Move = IA_Move_OBJ.Object;

    static ConstructorHelpers::FObjectFinder<UInputAction> IA_Attack_OBJ(TEXT("/Game/Paper2D/Input/Actions/IA_Attack"));
    IA_Attack = IA_Attack_OBJ.Object;

    // Input Mapping Context
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_SideScroller_OBJ(TEXT("/Game/Paper2D/Input/IMC_SideScroller"));
    IMC_SideScroller = IMC_SideScroller_OBJ.Object;

}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(IMC_SideScroller.Get(), 1);
    }
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(IA_Move.Get(), ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
        EnhancedInputComponent->BindAction(IA_Attack.Get(), ETriggerEvent::Triggered, this, &AMyPlayerController::Attack);
    }
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
   /* if (APawn* ControlledPawn = GetPawn())
    {
        FVector2D MovementVector = Value.Get<FVector2D>();
        ControlledPawn->AddMovementInput(FVector(MovementVector.X, 0.0f, 0.0f));
    }*/

    if (APawn* ControlledPawn = GetPawn())
    {
        if (AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(ControlledPawn))
        {
            MyCharacter->Move(Value);
        }
    }
}

void AMyPlayerController::Attack(const FInputActionValue& Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        if (AMyPaperCharacter* MyCharacter = Cast<AMyPaperCharacter>(ControlledPawn))
        {
            MyCharacter->Attack(Value);
        }
    }
}