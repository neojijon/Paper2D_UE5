// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "InputActionValue.h"
#include "PaperCharacter.h" // paper2D
//#include "PaperFlipbook.h"

//#include "Camera/CameraComponent.h"
//#include "GameFramework/SpringArmComponent.h"

//#include "GameFramework/CharacterMovementComponent.h"

#include "MyPaperCharacter.generated.h"

class UPaperFlipbook;
class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UPaperZDAnimationComponent;



/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)
class PAPER2D_UE5_API AMyPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMyPaperCharacter();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void Jump() override;
	virtual void StopJumping() override;


public:
	void Move(float Value);
	void Walk(const FInputActionValue& Value);

	//공격 Input 이벤트
	void Attack();

	

	UFUNCTION()
	void OnAttackFinished();

	void UpdateCharacter();

	void UpdateAnimation();

private:

	// Flipbook Animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPaperFlipbook> FB_Char_Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPaperFlipbook> FB_Char_Walk;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPaperFlipbook> FB_Char_Run;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPaperFlipbook> FB_Char_Attack01;


	// Movement state
	bool bIsAttacking;
	FVector2D MovementInput;

	// 카메라와 Spring Arm Components 를  추가함.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCharacterMovementComponent> Movement;

	// Add PaperZD
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperZD", meta = (AllowPrivateAccess = "true"))
	//UPaperZDAnimationComponent* AnimationComponent;
	TObjectPtr<class UPaperZDAnimationComponent> AnimationComponent;

};
