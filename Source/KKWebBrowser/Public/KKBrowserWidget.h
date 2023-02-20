// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "KKBrowserWidget.generated.h"

/**
 * 
 */
UCLASS()
class KKWEBBROWSER_API UKKBrowserWidget : public UWidget
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKKWebOnDataChange,const FString & ,Data);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKKWebOnExec);
	
	UKKBrowserWidget()
	{
		bIsVariable=true;
	}
	
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual const FText GetPaletteCategory() override;

	/*************************************** Data *************************************/
	
	// 显示Forward/Back/Reload控制Button
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb|Set")
	bool bShowControls = false;
	// 允许透明度控制
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb|Set")
	bool bSupportsTransparency = false;
	// 帧数
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb|Set")
	int32 BrowserFrameRate = 60;
	// 显示地址栏
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb|Set")
	bool bShowAddressBar = false;
	// 输出错误信息
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb|Set")
	bool bShowErrorMessage = false;
	// 显示初始的小圆圈
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb|Set")
	bool bShowInitialThrobber = false;

	// 初始化URL
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb|Set")
	FString InitialURL = TEXT("");

	// 当document没有指定Color时显示
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb")
	FColor BackgroundColor;

	// 期望的WebBrowser尺寸-无效;
	// 源码中没有使用;
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb")
	// FVector2D ViewportSize = FVector2D(300.f,300.f);
	
	// 允许Thumb按键控制
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb")
	bool bSupportsThumbMouseButtonNavigation = false;

	// 易变性 ?
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="KKWeb")
	bool bForceVolatile = true;
	

	/*************************************** Event *************************************/

	UFUNCTION(BlueprintCallable,Category="KKWeb")
	void KK_LoadUrl(const FString & Url );
	UFUNCTION(BlueprintCallable,Category="KKWeb")
	void KK_LoadString(const FString & Contents,const FString & DummyURL);
	UFUNCTION(BlueprintCallable,Category="KKWeb")
	void KK_Reload();
	UFUNCTION(BlueprintCallable,Category="KKWeb")
	void KK_GoBack();
	UFUNCTION(BlueprintCallable,Category="KKWeb")
	void KK_GoForward();
	UFUNCTION(BlueprintCallable,Category="KKWeb")
	void KK_ExecJavaScript(const FString & JspText);	
	

	/*************************************** delagate *************************************/

	UPROPERTY(BlueprintAssignable,Category="KKWeb|Event")
	FKKWebOnDataChange OnURLChange;
	UPROPERTY(BlueprintAssignable,Category="KKWeb|Event")
	FKKWebOnDataChange OnTitleChange;

	UPROPERTY(BlueprintAssignable,Category="KKWeb|Event")
	FKKWebOnExec OnLoadStarted;
	UPROPERTY(BlueprintAssignable,Category="KKWeb|Event")
	FKKWebOnExec OnLoadError;
	UPROPERTY(BlueprintAssignable,Category="KKWeb|Event")
	FKKWebOnExec OnLoadCompleted;

	
	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	
	TSharedPtr<class SWebBrowser> WebBrowserPtr = nullptr;
};
