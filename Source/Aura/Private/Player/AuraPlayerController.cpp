// Copyright Zopeplone


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//将输入映射上下文绑定到玩家控制器
	check(AuraContext)
	//在多人游戏中,如果有其他的玩家，此时在本机初始化其他玩家的时候，Subsystem为空
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem){
		Subsystem->AddMappingContext(AuraContext,0);
	}
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
void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CursorTrace();
}
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if(!CursorHit.bBlockingHit) return;
	//在光标下的对象是否实现了EnemyInterface
	//如果实现了EnemyInterface,则高亮
	
	//尝试将触碰到的Actor转换类型为IEnemyInterface(若该Actor继承了IEnemyInterface,则转化成功,反之失败)
	//如果转换失败返回null,转换成功返回该Actor
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	/*
	 *这里有一些情况需要分类讨论
	 * 1.LastActor不为null ThisActor为null  -LastActor取消高亮
	 * 2.LastActor不为null ThisActor不为null  
	 *		A. LastActor==ThisActor -什么都不做
	 *		B. LastActor!=ThisActor	-LastActor取消高亮 ThisActor高亮
	 * 3.LastActor为null ThisActor为null -什么都不做
	 * 4.LastActor为null ThisActor不为null - ThisActor高亮
	 */
	if(LastActor == nullptr)
	{
		//情况4
		if(ThisActor != nullptr)
		{
			//ThisActor高亮
			ThisActor->HighlightActor();
		}
		//else 情况3 什么都不做
	}
	else{
		//情况1
		if(ThisActor == nullptr)
		{
			//LastActor取消高亮
			LastActor->UnHighlightActor();
		}
		else
		{
			//情况2.B
			if(LastActor != ThisActor)
			{
				//LastActor取消高亮 ThisActor高亮
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			//else 情况2.A什么都不做
		}
	}
}
