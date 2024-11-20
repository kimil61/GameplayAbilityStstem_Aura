// Copyright ww stuido


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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


void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// 1. Enhanced Input 사용을 위한 컴포넌트 변환
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// 2. 입력 액션과 실제 함수 연결
	EnhancedInputComponent->BindAction(
		MoveAction,					// 어떤 액션에 대해
		ETriggerEvent::Triggered,		// 언제 실행할지
		this,							// 누가 처리할지
		&AAuraPlayerController::Move	// 어떤 함수로 처리할지
	);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// 1. 입력값을 2D 벡터로 변환
	// (X: 좌우 이동, Y: 전후 이동)
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	// 2. 카메라 방향 기준으로 이동 방향 계산
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// 3. 전방과 우측 방향 벡터 계산
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 4. 캐릭터 이동
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// 전후 이동 (W/S)
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		// 좌우 이동 (A/D)
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


