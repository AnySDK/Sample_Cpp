package com.anysdk.sample;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.view.LayoutInflater;

public class wrapper {
	public static native void nativeInitPlugins();
	public static native void nativeUnLoadPlugins();
	public static native String nativeGetCustomParam();
	public static native String nativeGetChannelId();
	
	//User相关函数
	public static native void nativeLogin();
	public static native void nativeLogout();
	public static native void nativeAccountSwitch();
	public static native void nativePause();
	public static native void nativeExit();
	public static native void nativeEnterPlatform();
	public static native void nativeHideToolBar();
	public static native void nativeShowToolBar();
	public static native void nativeRealNameRegister();
	public static native void nativeAntiAddictionQuery();
	public static native void nativeSubmitLoginGameRole();
	public static native boolean nativeUserIsFunctionSupported(String name);
	public static native boolean nativeIsLogined();
	public static native String nativeGetUserId();
	public static native void nativeExcuteFunction(String name);
	
	//IAP相关函数
	public static native void nativePay();
	public static native void nativeResetPayState();
	public static native void nativePayMode(String id);
	public static native String nativeGetOrderId();
		

	
	//Analytics相关函数
	public static native boolean nativeAnalyticsIsFunctionSupported(String name);
	public static native void nativeStartSession();
	public static native void nativeStopSession();
	public static native void nativeSetSessionContinueMillis();
	public static native void nativeLogError();
	public static native void nativeLogEvent();
	public static native void nativeLogTimedEventBegin();
	public static native void nativeLogTimedEventEnd();
	public static native void nativeSetCaptureUncaughtException();
	public static native void nativeSetAccount();
	public static native void nativeOnChargeRequest();
	public static native void nativeOnChargeSuccess();
	public static native void nativeOnChargeFail();
	public static native void nativeOnChargeOnlySuccess();
	public static native void nativeOnPurchase();
	public static native void nativeOnUse();
	public static native void nativeOnReward();
	public static native void nativeStartLevel();
	public static native void nativeFinishLevel();
	public static native void nativeFailLevel();
	public static native void nativeStartTask();
	public static native void nativeFinishTask();
	public static native void nativeFailTask();
	
	//Share相关函数
	public static native void nativeShare();
	
	//Ads相关函数
	public static native void nativeShowAds(int type, int index);
	public static native void nativeHideAds(int type, int index);
	public static native void nativePreloadAds(int type, int index);
	public static native void nativeQueryPoints();
	public static native float nativeSpendPoints();
	
	
	//Social相关函数
	public static native void nativeSignIn();
	public static native void nativeSignOut();
	public static native void nativeSubmitScore();
	public static native void nativeShowLeaderboard();
	public static native void nativeUnlockAchievement();
	public static native void nativeShowAchievements();
	
	
	//Push相关函数
	public static native void nativeStartPush();
	public static native void nativeClosePush();
	public static native void nativeSetAlias();
	public static native void nativeDelAlias();
	public static native void nativeSetTags();
	public static native void nativeDelTags();
	
	
	//Crash相关函数
	public static native void nativeReportException();
	public static native void nativeSetUserIdentifier();
	public static native void nativeLeaveBreadcrumb();
	

	//REC相关函数
	public static native boolean nativeRECIsFunctionSupported(String name);
	public static native void nativeStartRecording();
	public static native void nativeStopRecording();
	public static native void nativeRECShare();
	public static native void nativePauseRecording();
	public static native void nativeResumeRecording();
	public static native boolean nativeIsAvailable();
	public static native void nativeRECShowToolBar();
	public static native void nativeRECHideToolBar();
	public static native boolean nativeIsRecording();
	public static native void nativeShowVideoCenter();
	public static native void nativeRECEnterPlatform();
	public static native void nativeSetMetaData();
	
	//AdTracking相关函数
    public static native boolean nativeAdTrackingIsFunctionSupported(String name);
    public static native void nativeOnRegister();
    public static native void nativeOnLogin();
    public static native void nativeOnPay();
    public static native void nativeTrackEvent();
    public static native void nativeOnStartToPay();
    public static native void nativeOnCreateRole();
    public static native void nativeOnLevelUp();
	
	
	
	
	
	

}
