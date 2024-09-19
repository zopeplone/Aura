// Copyright Zopeplone


#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	//将网格碰撞检测中的Visibility通道打开,
	//让AuraPlayerController中的GetHitResultUnderCursor能够在ECC_Visibility通道碰撞到敌人
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	//初始化敌人类的AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	//开启服务端复制,将该组件的状态和行为在网络环境下从服务器同步到客户端
	AbilitySystemComponent->SetIsReplicated(true);
	//服务端复制的方式-Minimal（适合AI）
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	//初始化敌人类的AttributeSet
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighlightActor()
{
	//获取该实例的网格实例,在网格中设置CustomDepth为后期处理高亮的CustomDepth值
	//当该网格的CustomDepth值为高亮的CustomDepth,则后期处理高亮会在这个网格上渲染
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	//为武器也设置高亮
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	//初始化AuraEnemy的ActorInfo
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	
}
