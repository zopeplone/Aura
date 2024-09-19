// Copyright Zopeplone

#pragma once
#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"
//添加前向声明
class UAttributeSet;
class UAbilitySystemComponent;
//标识为抽象类,不可直接拖拽至场景中
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();
	//获取AbilitySystem,继承IAbilitySystemInterface接口,重写函数
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//获取AttributeSet
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//角色武器骨骼网格指针
	UPROPERTY(EditAnywhere,Category="Combat")//在任意地方可以修改，分类为战斗
	TObjectPtr<USkeletalMeshComponent> Weapon;
	//GAS系统
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	
};
