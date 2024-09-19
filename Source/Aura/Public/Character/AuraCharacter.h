// Copyright Zopeplone

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	//当一个 Pawn 被一个新的 Controller 接管时的回调函数
	virtual void PossessedBy(AController* NewController) override;
	//当 PlayerState 在客户端上通过网络复制发生变化时,OnRep_PlayerState 函数会被自动调用,它主要用于处理 PlayerState 更新的回调
	// PlayerState 初始化时也会调用该函数
	virtual void OnRep_PlayerState() override;
private:
	void InitAbilityActorInfo();
};
