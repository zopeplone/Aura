// Copyright Zopeplone


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; //设置为true，角色将朝移动的方向旋转
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f); //旋转速率
	GetCharacterMovement()->bConstrainToPlane = true; //约束到平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true; //设置了上面一项为true，且此项设置为true，则在开始时与地面对齐

	//设置使用控制器选择Pitch，Yaw，Roll的值。
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
}



void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//为服务器初始化 AbilityActorInfo
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//为客户端初始化 AbilityActorInfo
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	//初始化PlayerState中ASC的信息
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	//将PlayerState中的ASC和AS赋给Character,因为在Character构造函数中没有为ASC和AS赋值
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();


	//InitOverlay,此时PlayerController,PlayerState,ASC,AS都初始化好了,可以将这些数据与WidgetController绑定
	//在多人游戏的客户端中，这个PlayerController可能为空，因为每个玩家只能拥有自己的PlayerController
	//只有对于自己控制的角色，PlayerController不为空，当然，也不需要在自己的屏幕上添加其他角色的HUD
	if(AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		//如果HUD有效，那么我们可以将数据通过HUD与WidgetController绑定
		if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(PlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}
	
}
