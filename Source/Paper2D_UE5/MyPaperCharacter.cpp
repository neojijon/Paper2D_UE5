// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UObject/ConstructorHelpers.h"

AMyPaperCharacter::AMyPaperCharacter()
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



void AMyPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(IMC_SideScroller, 1);

            UE_LOG(LogTemp, Warning, TEXT("IMC_SideScroller"));
        }
    }

}


void AMyPaperCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //추가 구현하면 됨.

}



void AMyPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(IA_Move.Get(), ETriggerEvent::Triggered, this, &AMyPaperCharacter::Move);
        EnhancedInputComponent->BindAction(IA_Attack.Get(), ETriggerEvent::Triggered, this, &AMyPaperCharacter::Attack);
    }

}


void AMyPaperCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    AddMovementInput(FVector(MovementVector.X, 0.0f, 0.0f));

    UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent"));
}

void AMyPaperCharacter::Attack(const FInputActionValue& Value)
{
    // 공격 로직을 여기에 구현
    UE_LOG(LogTemp, Warning, TEXT("Attack!"));
}


