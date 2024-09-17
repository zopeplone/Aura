// Copyright Zopeplone


#include "Character/AuraCharacterBase.h"

// 构造函数
AAuraCharacterBase::AAuraCharacterBase()
{
 	// 基类不需要每一帧都触发事件
	PrimaryActorTick.bCanEverTick = false;
	//在角色中创建可视化的武器组件
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	//将武器（Weapon 组件）附加到角色的骨骼系统上，具体附加的位置是角色的 "WeaponHandSocket" 插槽
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	//给武器设置无需碰撞
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

