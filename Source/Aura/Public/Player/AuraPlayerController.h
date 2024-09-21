// Copyright Zopeplone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */
//前向声明,减少编译时间,去除循环依赖
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere,Category = "Input")
	//输入映射上下文
	TObjectPtr<UInputMappingContext> AuraContext;
	UPROPERTY(EditAnywhere,Category = "Input")
	//InputAction
	TObjectPtr<UInputAction> MoveAction;
	/**
	 * 接收输入,控制角色移动
	 * @param InputActionValue MoveAction的输入
	 */
	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();
	TObjectPtr<IEnemyInterface> LastActor;
	TObjectPtr<IEnemyInterface> ThisActor;
};
