// Copyright Zopeplone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"
//标识为抽象类,不可直接拖拽至场景中
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//角色武器骨骼网格指针
	UPROPERTY(EditAnywhere,Category="Combat")//在任意地方可以修改，分类为战斗
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
};
