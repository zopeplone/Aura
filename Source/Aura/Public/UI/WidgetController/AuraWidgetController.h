// Copyright Zopeplone

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	FWidgetControllerParams(){};
	FWidgetControllerParams(APlayerController* PC,APlayerState* PS,
		UAbilitySystemComponent* ASC,UAttributeSet* AS):
	PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS){};
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};
/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	//为该WidgetController设置关联的数据
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	//向绑定了该WidgetController的Widget广播初始值
	virtual void BroadcastInitialValues();
	//设置监听数据变化的依赖绑定
	virtual void BindCallbacksToDependencies();
protected:
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
