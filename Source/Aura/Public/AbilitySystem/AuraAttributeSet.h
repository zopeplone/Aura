// Copyright Zopeplone

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
//属性访问器简写宏
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}
	FGameplayEffectContextHandle EffectContextHandle;
	//Source 代表这个Effect是从哪个Actor释放的,Target代表自身(拥有该AttributeSet的角色)
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC=nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor=nullptr;
	UPROPERTY()
	AController* SourceController=nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter=nullptr;
	UPROPERTY()
	UAbilitySystemComponent* TargetASC=nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor=nullptr;
	UPROPERTY()
	AController* TargetController=nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter=nullptr;
};


UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	//指定哪些属性需要在服务器和客户端之间同步，并定义每个属性的复制条件（Replication Condition）
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	//将生命法力值限定在0-Max中
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//在GameplayEffect被添加时的回调
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	//生命值
	//ReplicatedUsing为当服务端修改Health数值时的回调，拥有Replicated属性时，其值会从服务器自动复制到客户端
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;
	//生命值的属性访问器
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth,Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);
	//法力值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMana,Category="Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);


	//生命值回调
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	//法力值回调
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
private:
	//从PostGameplayEffectExecute的Data中获取所有的属性,包括ContextHandle,Actor,Character等等
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& Props);
};
