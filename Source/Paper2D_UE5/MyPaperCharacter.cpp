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

    //카메라, 스프링암 컴퍼넌트를 값 세팅
    // Spring Arm Component
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.0f;
    SpringArm->SetRelativeRotation(FRotator(-10.0f, -90.0f, 0.0f)); //횡스크롤 화면 
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

    if (GetSprite() != nullptr)
    {
        GetSprite()->SetFlipbook(FB_Char_Idle);
        //GetSprite 이벤트 함수 등록
        GetSprite()->OnFinishedPlaying.AddDynamic(this, &AMyPaperCharacter::OnAttackFinished);

        UE_LOG(LogTemp, Warning, TEXT("OnFinishedPlaying.AddDynamic"));
    }
}


void AMyPaperCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //추가 구현하면 됨.
    UpdateCharacter();

}






void AMyPaperCharacter::Move(const FInputActionValue& Value)
{
    if(!bIsAttacking)
    {
        //케릭터 움직임
        FVector2D MovementVector = Value.Get<FVector2D>();
        AddMovementInput(FVector(1, 0.0f, 0.0f), MovementVector.X);


        if (MovementVector.X < 0)
        {
            const FRotator YawRotation(0, 180, 0);
        }
        else if (MovementVector.X > 0)
        {
            const FRotator YawRotation(0, 0, 0);
        }
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




void AMyPaperCharacter::UpdateCharacter()
{
    // Update animation to match the motion
    UpdateAnimation();

    // Now setup the rotation of the controller based on the direction we are travelling
    const FVector PlayerVelocity = GetVelocity();
    float TravelDirection = PlayerVelocity.X;
    // Set the rotation so that the character faces his direction of travel.
    if (Controller != nullptr)
    {
        if (TravelDirection < 0.0f)
        {
            Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
        }
        else if (TravelDirection > 0.0f)
        {
            Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
        }
    }
}



void AMyPaperCharacter::UpdateAnimation()
{
    if (!bIsAttacking)
    {
        const FVector PlayerVelocity = GetVelocity();
        const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

        // Are we moving or standing still?
        UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? FB_Char_Run : FB_Char_Idle;
        if (GetSprite()->GetFlipbook() != DesiredAnimation)
        {
            GetSprite()->SetFlipbook(DesiredAnimation);
        }

    }
    
}
