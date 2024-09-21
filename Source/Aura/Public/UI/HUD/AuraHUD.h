// Copyright Zopeplone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	//获取WidgetController
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	//初始化WidgetController和Widget
	void InitOverlay(APlayerController* PC,APlayerState* PS,
		UAbilitySystemComponent* ASC,UAttributeSet* AS);
	
//在此时，我们不能在BeginPlay中初始化WidgetController，
//因为在BeginPlay时，我们不知道ASC，AS等数据是否已经初始化完毕
//我们必须等数据都初始化完毕后，再去初始化WidgetController，我们需要一个时机去调用InitOverlay
private:
	//WidgetController
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	//WidgetController所需的WidgetController类，可以在蓝图中设置
	//（因为子类可能所需的WidgetController不同）
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	
	//可以在蓝图中设置所需的Widget类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
};
