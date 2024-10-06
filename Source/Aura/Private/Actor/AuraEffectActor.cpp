// Copyright Zopeplone


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		//去除InfiniteEffect
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		TArray<FActiveGameplayEffectHandle> RemovedKeys;
		for(TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*>& Tuple:ActiveEffectHandles)
		{
			if(TargetASC == Tuple.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(Tuple.Key);
				RemovedKeys.Add(Tuple.Key);
			}
		}
		for(auto& Key:RemovedKeys)
		{
			ActiveEffectHandles.Remove(Key);
		}
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//这个函数是工具库,可以获取实现了IAbilitySystem接口的Actor的AbilitySystem
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(!TargetASC) return;
	//检查是否Class不为null
	check(GameplayEffectClass)
	//获取ASC的EffectContext
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	//为ContextHandle添加源（就是这个效果的添加者）
	EffectContextHandle.AddSourceObject(this);
	//制作一个Spec
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass,ActorLevel,EffectContextHandle);
	//为Target添加效果
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	//如果这个Effect为无限时长的类,且当前无限时长类的policy为RemovedOnEndOverlap,则需要存储ActiveEffectHandle,以便后续删除
	bool bIsInfinite = false;
	if(EffectSpecHandle.Data->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
	{
		bIsInfinite = true;
	}
	if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle,TargetASC);
	}
}




