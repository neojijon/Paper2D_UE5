// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPaperCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyGameModeBase::AMyGameModeBase()
{
	// 블루프린터 클래스를 디폴트 Pawn 클래스로 세팅하는 방법
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Paper2D/BP_Character"));	
		
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

		
	static ConstructorHelpers::FClassFinder<APlayerController> ControllClass(TEXT("/Game/Paper2D/BP_MyPlayerController"));

	if (ControllClass.Class != NULL)
	{
		PlayerControllerClass = ControllClass.Class;
	}

	//일반 C++ 클래스를  세팅하는 방법
	//DefaultPawnClass = AMyPaperCharacter::StaticClass();
	//PlayerControllerClass = AMyPlayerController::StaticClass();
}