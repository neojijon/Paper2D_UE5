// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaperCharacter.h"

#include "PaperFlipbookComponent.h"
#include "EnhancedInputComponent.h"

#include "UObject/ConstructorHelpers.h"

//#include "GameFramework/SpringArmComponent.h"
//#include "Camera/CameraComponent.h"



AMyPaperCharacter::AMyPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    //인풋관련 초기 세팅
    // Input Actions
    static ConstructorHelpers::FObjectFinder<UInputAction> IA_Move_OBJ(TEXT("/Game/Paper2D/Input/Actions/IA_Move"));
    IA_Move = IA_Move_OBJ.Object;

    static ConstructorHelpers::FObjectFinder<UInputAction> IA_Attack_OBJ(TEXT("/Game/Paper2D/Input/Actions/IA_Attack"));
    IA_Attack = IA_Attack_OBJ.Object;

    //애니메이션 초기 세팅
    // Flipbook Animations
    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FB_Idle_OBJ(TEXT("/Game/Paper2D/Character/FB_Char_Idle"));
    FB_Char_Idle = FB_Idle_OBJ.Object;

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FB_Run_OBJ(TEXT("/Game/Paper2D/Character/FB_Char_Run"));
    FB_Char_Run = FB_Run_OBJ.Object;

    static ConstructorHelpers::FObjectFinder<UPaperFlipbook> FB_Attack01_OBJ(TEXT("/Game/Paper2D/Character/FB_Char_Attack01"));
    FB_Char_Attack01 = FB_Attack01_OBJ.Object;

    //카메라, 스프링암 컴퍼넌트를 값 세팅
    // Spring Arm Component
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 500.0f;
    SpringArm->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); //횡스크롤 화면 
    //SpringArm->SetWorldRotation(FRotator(0.0f, 0.0f, -90.0f));
    SpringArm->bDoCollisionTest = false;
    SpringArm->bInheritPitch = false;
    SpringArm->bInheritYaw = false;
    SpringArm->bInheritRoll = false;

    // Camera Component
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
    

    bIsAttacking = false;
}



void AMyPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

    bIsAttacking = false;
    GetSprite()->SetFlipbook(FB_Char_Idle);

    if (GetSprite())
    {
        //GetSprite 이벤트 함수 등록
        GetSprite()->OnFinishedPlaying.AddDynamic(this, &AMyPaperCharacter::OnAttackFinished);
    }
}


void AMyPaperCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //추가 구현하면 됨.
    UpdateAnimation();

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
    if(!bIsAttacking)
    {
        //케릭터 움직임
        FVector2D MovementVector = Value.Get<FVector2D>();
        AddMovementInput(FVector(MovementVector.X, 0.0f, 0.0f));

        UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent"));
    }    
}

void AMyPaperCharacter::Attack(const FInputActionValue& Value)
{
    // 공격 로직을 여기에 구현
    if (!bIsAttacking)
    {
        bIsAttacking = true;
        GetSprite()->SetFlipbook(FB_Char_Attack01);
        GetSprite()->SetLooping(false);        
        GetSprite()->PlayFromStart();

        /*GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
        {
            bIsAttacking = false;
        });*/

        UE_LOG(LogTemp, Warning, TEXT("Attack!"));
    }
}


void AMyPaperCharacter::OnAttackFinished()
{
    UE_LOG(LogTemp, Warning, TEXT("OnAttackFinished!"));

    bIsAttacking = false;
    GetSprite()->SetLooping(true);
    GetSprite()->Play();
    UpdateAnimation();

   /* GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
    {
        bIsAttacking = false;
    });*/
}


void AMyPaperCharacter::UpdateAnimation()
{
    if (!bIsAttacking)
    {        
        if (MovementInput.SizeSquared() > 0.0f)
        {
            GetSprite()->SetFlipbook(FB_Char_Run);
        }
        else
        {
            GetSprite()->SetFlipbook(FB_Char_Idle);
        }
    }
    
}
