// Copyright ww stuido


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	// Enhanced Input System 설정
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);

	bShowMouseCursor = true;							// 마우스 커서 보이게 설정
	DefaultMouseCursor = EMouseCursor::Default;		// 기본 커서 모양 설정

	FInputModeGameAndUI InputModeData;					// 게임과 UI 모두 입력 받는 모드
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);		// 마우스를 화면에 가두지 않음
	InputModeData.SetHideCursorDuringCapture(false);	// 마우스 캡처 중에도 커서 보이게
	SetInputMode(InputModeData);						// 설정 적용
	
}

