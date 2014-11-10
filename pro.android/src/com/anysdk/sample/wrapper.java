package com.anysdk.sample;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.view.LayoutInflater;

public class wrapper {
	public static native void nativeDestroy();
	public static native void nativePause();
	public static native void nativeExit();
	public static native void nativeInitPlugins();
	public static native void nativeUnLoadPlugins();
	public static native void nativeLogin();
	public static native void nativeLogout();
	public static native void nativeAccountSwitch();
	public static native void nativePay();
	public static native void nativeResetPayState();
	public static native void nativeEnterPlatform();
	public static native void nativeHideToolBar();
	public static native void nativeShowToolBar();
	public static native void nativeRealNameRegister();
	public static native void nativeAntiAddictionQuery();
	public static native void nativeSubmitLoginGameRole();
	public static native void nativePayMode(String id);
	public static native boolean nativeIsFunctionSupported(String name);
	public static native void nativeExcuteFunction(String name);
	
	public static native String nativeGetCustomParam();
	public static native String nativeGetChannelId();
	
	public static native void nativeStartSession();
	public static native void nativeStopSession();
	
	public static native void nativeShare();
	
	public static native void nativeShowAds();
	public static native void nativeHideAds();
	
	
	public static native void nativeSubmitScore();
	public static native void nativeShowLeaderboard();
	public static native void nativeUnlockAchievement();
	public static native void nativeShowAchievements();
	
	
	public static native void nativeStartPush();
	public static native void nativeClosePush();
	public static native void nativeSetAlias();
	public static native void nativeDelAlias();
	public static native void nativeSetTags();
	public static native void nativeDelTags();
	
	
	
	
	
	

}
