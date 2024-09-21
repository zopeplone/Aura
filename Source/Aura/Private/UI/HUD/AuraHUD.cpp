// Copyright Zopeplone


#include "UI/HUD/AuraHUD.h"
//必须加上这一个include,否则OverlayWidgetClass类型不完整
#include "UI/Widget/AuraUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC,APlayerState* PS,
		UAbilitySystemComponent* ASC,UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("OverlayWidgetClass没有在蓝图中初始化"))
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass没有在蓝图中初始化"))

	
	//创建Widget，其类为蓝图上放置的Overlay类
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);

	
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	//让WidgetController广播初始值，因为此时Widget已经绑定好了WidgetController
	WidgetController->BroadcastInitialValues();
	//添加进视口
	Widget->AddToViewport();
	
}


