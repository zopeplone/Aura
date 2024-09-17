// Copyright Zopeplone


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//将输入映射上下文绑定到玩家控制器
	check(AuraContext)
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem)
	Subsystem->AddMappingContext(AuraContext,0);
	//光标设置
	//在游戏中始终显示鼠标光标
	bShowMouseCursor = true;
	//光标为普通的箭头光标
	DefaultMouseCursor = EMouseCursor::Default;
	//输入模式，允许同时捕捉游戏输入（如角色控制）和用户界面输入（如点击按钮）
	FInputModeGameAndUI InputModeData;
	//设置鼠标是否锁定在视口内（不锁定）
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//捕获输入时不隐藏光标
	InputModeData.SetHideCursorDuringCapture(false);
	//将输入模式设置为前面定义的 InputModeData
	SetInputMode(InputModeData);
}


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//提取二维向量输入
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	//获取当前相机的方向
	const FRotator Rotation = GetControlRotation();
	//我们只取玩家视角的 Yaw（即左右旋转），忽略俯仰和滚动
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
	//基于当前的 YawRotation，计算出世界坐标系下面向的“前方”方向的单位向量（即朝向前方的方向）
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//计算面向“右方”方向的单位向量
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//获取当前控制的 Pawn,即角色,若有当前角色才执行
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
	/*
	 *为什么这里GetUnitAxis(EAxis::X),但是 InputAxisVector.Y
	 * GetUnitAxis(EAxis::X) 表示角色的“前方方向”，而 InputAxisVector.Y 代表玩家输入的前后移动（如按下 W 或 S）
	 * 所以当玩家想向前或向后移动时，我们将角色的前方方向（即 X 轴方向）与玩家的前后移动输入相结合
	 */
}
