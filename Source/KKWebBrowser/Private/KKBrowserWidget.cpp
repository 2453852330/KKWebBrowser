// Fill out your copyright notice in the Description page of Project Settings.


#include "KKBrowserWidget.h"
#include "IWebBrowserDialog.h"
#include "SWebBrowser.h"

void UKKBrowserWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UKKBrowserWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	if (WebBrowserPtr)
	{
		WebBrowserPtr.Reset();
	}
}

const FText UKKBrowserWidget::GetPaletteCategory()
{
	return FText::FromString(TEXT("KKWebBrowserWidget"));
}

void UKKBrowserWidget::KK_LoadUrl(const FString& Url)
{
	if (WebBrowserPtr)
	{
		WebBrowserPtr->LoadURL(Url);
	}
}

void UKKBrowserWidget::KK_LoadString(const FString& Contents, const FString& DummyURL)
{
	if (WebBrowserPtr)
	{
		WebBrowserPtr->LoadString(Contents,DummyURL);
	}
}

void UKKBrowserWidget::KK_Reload()
{
	if (WebBrowserPtr)
	{
		WebBrowserPtr->Reload();
	}
}

void UKKBrowserWidget::KK_GoBack()
{
	if (WebBrowserPtr)
	{
		WebBrowserPtr->GoBack();
	}
}

void UKKBrowserWidget::KK_GoForward()
{
	if (WebBrowserPtr)
	{
		WebBrowserPtr->GoForward();
	}
}

void UKKBrowserWidget::KK_ExecJavaScript(const FString& JspText)
{
	if (WebBrowserPtr)
	{
		WebBrowserPtr->ExecuteJavascript(JspText);
	}
}


TSharedRef<SWidget> UKKBrowserWidget::RebuildWidget()
{
	if ( IsDesignTime() )
	{
		return SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("KK Web Browser")))
			];
	}
	
	WebBrowserPtr = SNew(SWebBrowser)
	.BackgroundColor(BackgroundColor)
	.ShowControls(bShowControls)
	.SupportsTransparency(bSupportsTransparency)
	// .ViewportSize(ViewportSize)
	.BrowserFrameRate(BrowserFrameRate)
	.ShowAddressBar(bShowAddressBar)
	.ShowErrorMessage(bShowErrorMessage)
	.ShowInitialThrobber(bShowInitialThrobber)
	.InitialURL(InitialURL)
	.SupportsThumbMouseButtonNavigation(bSupportsThumbMouseButtonNavigation)
	// .Clipping(Clipping)
	// .Cursor()
	.ForceVolatile(bForceVolatile)
	// 不支持调节;
	// .RenderOpacity(WebRenderOpacity)
	
	// .RenderTransform()

	/*************************************** 多播动态代理不支持返回值,所以没有公开带返回值的事件 *************************************/
	
	// 返回True终止调用;
	// .OnBeforeNavigation_Lambda([](const FString& Str, const FWebNavigationRequest& Request)
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("OnBeforeNavigation_Lambda->%s"),*Str);
	// 	return false;
	// })
	// .OnBeforePopup_Lambda([](FString URL,FString Frame)
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("OnBeforePopup_Lambda->%s|%s"),*URL,*Frame);
	// 	return true;
	// })
	
	// Window
	// .OnCloseWindow_Lambda([](const TWeakPtr<IWebBrowserWindow>& WebWindow)
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("OnCloseWindow_Lambda"));
	// 	return true;
	// })
	// .OnCreateWindow_Lambda([](const TWeakPtr<IWebBrowserWindow>& A, const TWeakPtr<IWebBrowserPopupFeatures>& B)
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("OnCreateWindow_Lambda"));
	// 	return true;
	// })
	// .OnDragWindow_Lambda([](const FPointerEvent&  MouseEvent )
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("OnDragWindow_Lambda"));
	// 	return true;
	// })

	
	// load
	.OnLoadCompleted_Lambda([this]()
	{
		// UE_LOG(LogTemp,Warning,TEXT("OnLoadCompleted_Lambda"));
		if (OnLoadCompleted.IsBound())
		{
			OnLoadCompleted.Broadcast();
		}
	})
	.OnLoadError_Lambda([this]()
	{
		// UE_LOG(LogTemp,Warning,TEXT("OnLoadError_Lambda"));
		if (OnLoadError.IsBound())
		{
			OnLoadError.Broadcast();
		}
	})
	.OnLoadStarted_Lambda([this]()
	{
		// UE_LOG(LogTemp,Warning,TEXT("OnLoadStarted_Lambda"));
		if (OnLoadStarted.IsBound())
		{
			OnLoadStarted.Broadcast();
		}
	})

	
	// 类似于网页中F12调用各种API,返回True表示结束;
	// .OnLoadUrl_Lambda([](const FString& Method, const FString& Url, FString&  Response )
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("OnLoadUrl_Lambda->Method:%s | Url:%s | Response: %s"),*Method,*Url,*Response);
	// 	return false;
	// })
	// .OnShowDialog_Lambda([](const TWeakPtr<IWebBrowserDialog>& Dialog)
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("OnShowDialog_Lambda"));
	// 	return EWebBrowserDialogEventResponse::Handled;
	// })

	
	.OnTitleChanged_Lambda([this](const FText& Text)
	{
		// UE_LOG(LogTemp,Warning,TEXT("OnTitleChanged_Lambda->%s"),*Text.ToString());
		if (OnTitleChange.IsBound())
		{
			OnTitleChange.Broadcast(Text.ToString());
		}
	})
	.OnUrlChanged_Lambda([this](const FText& Url)
	{
		// UE_LOG(LogTemp,Warning,TEXT("OnUrlChanged_Lambda->%s"),*Url.ToString());
		if (OnURLChange.IsBound())
		{
			OnURLChange.Broadcast(Url.ToString());
		}
	})

	
	// .OnDismissAllDialogs_Lambda([]()
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("OnDismissAllDialogs_Lambda"));
	// })
	// .OnSuppressContextMenu_Lambda([]()
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("OnSuppressContextMenu_Lambda"));
	// 	return true;
	// })
	;
	
	return WebBrowserPtr.ToSharedRef();
}
