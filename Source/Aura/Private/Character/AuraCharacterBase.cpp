// Copyright Zopeplone


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// 基类不需要每一帧都触发事件
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

