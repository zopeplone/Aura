// Copyright Zopeplone

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	//获取AbilitySystem,继承IAbilitySystemInterface接口,重写函数
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//获取AttributeSet
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	//GAS系统
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
