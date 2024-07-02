// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "MyPaperCharacter_ZD.generated.h"


class UPaperFlipbook;
class USpringArmComponent;
class UCameraComponent;

class UCharacterMovementComponent;
class UPaperZDAnimationComponent;


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PAPER2D_UE5_API AMyPaperCharacter_ZD : public APaperCharacter
{
	GENERATED_BODY()
public:
	AMyPaperCharacter_ZD();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Jump() override;
	virtual void StopJumping() override;


public:
	void Move(float Value);
	void Walk(float Value);

	//공격 Input 이벤트
	void Attack();



	//UFUNCTION()
	//void OnAttackFinished();

	void TurnRight(float value);

private:

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
	TObjectPtr<class UPaperZDAnimationComponent> AnimationComponent;
};
