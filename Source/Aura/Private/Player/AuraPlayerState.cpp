// Copyright Zopeplone


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	//服务器更新客户端的频率
	NetUpdateFrequency = 100.f;
	//初始化敌人类的AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	//开启服务端复制,将该组件的状态和行为在网络环境下从服务器同步到客户端
	AbilitySystemComponent->SetIsReplicated(true);
	//服务端复制的方式-Mixed（适合主角）
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	//初始化敌人类的AttributeSet
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
