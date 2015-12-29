package com.anysdk.sample;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Vector;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import com.anysdk.framework.AdsWrapper;
import com.anysdk.framework.IAPWrapper;
import com.anysdk.framework.PluginWrapper;
import com.anysdk.framework.PushWrapper;
import com.anysdk.framework.ShareWrapper;
import com.anysdk.framework.SocialWrapper;
import com.anysdk.framework.UserWrapper;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.AlertDialog;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.DataSetObserver;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.SimpleAdapter;

public class MainActivity extends Activity {
	
	static {
		System.loadLibrary("game");
	}

	
	private static final String TAG_STRING = "ANYSDK";
	private static Activity mAct;
	private static Handler mUIHandler;
	private ListView mainListView;
	private SimpleAdapter adapter;
	private List<Map<String, String>> sysList = new ArrayList<Map<String, String>>();

	private String[] mainStrings = new String[] { "User System", "IAP System",
			"Share System", "Social System", "Ads System", "Analytics System",
			"Push System", "Crash System", "REC System"};

	private String[] userStrings = new String[] { "return", "login",
			"isLogined", "getUserID" };

	private String[] iapStrings = new String[] { "return", "payForProduct",
			"getOrderId" };

	private String[] shareStrings = new String[] { "return", "share" };

	private String[] socialStrings = new String[] { "return", "signIn",
			"signOut", "submitScore", "showLeaderboard", "unlockAchievement",
			"showAchievements" };

	private String[] adsStrings = new String[] { "return", "Banner",
			"FullScreen", "MoreAPP", "OfferWall", "queryPoints", "spendPoints" };
	
	private String[] adsFuntionStrings = new String[] {"return", "preloadAds1","preloadAds2",
			"showAds1", "showAds2","hideAds1","hideAds2"};

	private String[] analyticsStrings = new String[] { "return",
			"startSession", "stopSession", "setSessionContinueMillis",
			"logError", "logEvent", "logTimedEventBegin", "logTimedEventEnd" };

	private String[] pushStrings = new String[] { "return", "startPush",
			"closePush", "setAlias", "delAlias", "setTags", "delTags" };

	private String[] crashStrings = new String[] { "return",
			"setUserIdentifier", "reportException", "leaveBreadcrumb" };

	private String[] recStrings = new String[] { "return", "startRecording",
			"stopRecording", "share" };

	@Override
	protected void onCreate(Bundle savedInstanceState) {

		super.onCreate(savedInstanceState);
		

		mAct = this;
		mUIHandler = new Handler();
		PluginWrapper.init(this);
		wrapper.nativeInitPlugins();

		updataData("main","");
		mainListView = new ListView(this);
		adapter = new SimpleAdapter(this, sysList, R.layout.activity_first,
				new String[] { "title" }, new int[] { R.id.title });
		mainListView.setAdapter(adapter);
		mainListView.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				HashMap<String, String> map = (HashMap<String, String>) mainListView
						.getItemAtPosition(arg2);
				String tagString = map.get("tag");
				String titleString = map.get("title");
				String lastString = map.get("last");
				if (titleString.equals("return")) {
					updataData(lastString, "main");
					adapter.notifyDataSetChanged();
					mainListView.setAdapter(adapter);
				} else if (tagString.equals("main")) {
					if (titleString.equals("User System")) {
						updataData("user",tagString);
					} else if (titleString.equals("IAP System")) {
						updataData("iap",tagString);
					} else if (titleString.equals("Ads System")) {
						updataData("ads",tagString);
					} else if (titleString.equals("Social System")) {
						updataData("social",tagString);
					} else if (titleString.equals("Share System")) {
						updataData("share",tagString);
					} else if (titleString.equals("Analytics System")) {
						updataData("analytics",tagString);
					} else if (titleString.equals("Push System")) {
						updataData("push",tagString);
					} else if (titleString.equals("Crash System")) {
						updataData("crash",tagString);
					} else if (titleString.equals("REC System")) {
						updataData("rec",tagString);
					}
					adapter.notifyDataSetChanged();
					mainListView.setAdapter(adapter);
				} else if(tagString.equals("ads")){
					if (titleString.equals("Banner")) {
						updataData("Banner",tagString);
					} else if (titleString.equals("FullScreen")) {
						updataData("FullScreen",tagString);
					} else if (titleString.equals("MoreAPP")) {
						updataData("MoreAPP",tagString);
					} else if (titleString.equals("OfferWall")) {
						updataData("OfferWall",tagString);
					} else {
						Controller.onClick(tagString, titleString);
					}
					adapter.notifyDataSetChanged();
					mainListView.setAdapter(adapter);
				}
				else {
					Controller.onClick(tagString, titleString);
				}

			}
		});

		setContentView(mainListView);
	}

	private void updataData(String tag,String last) {
		sysList.clear();
		List<String> list = new ArrayList<String>();
		if (tag.equals("main")) {
			list.addAll(Arrays.asList(mainStrings));
		} else if (tag.equals("user")) {
			list.addAll(Arrays.asList(userStrings));
			list = Controller.extendUserFunction(list);
		} else if (tag.equals("iap")) {
			list.addAll(Arrays.asList(iapStrings));
		} else if (tag.equals("share")) {
			list.addAll(Arrays.asList(shareStrings));
		} else if (tag.equals("ads")) {
			list.addAll(Arrays.asList(adsStrings));
		} else if (tag.equals("analytics")) {
			list.addAll(Arrays.asList(analyticsStrings));
			list = Controller.extendAnalyticsFunction(list);
		} else if (tag.equals("social")) {
			list.addAll(Arrays.asList(socialStrings));
		} else if (tag.equals("push")) {
			list.addAll(Arrays.asList(pushStrings));
		} else if (tag.equals("crash")) {
			list.addAll(Arrays.asList(crashStrings));
		} else if (tag.equals("rec")) {
			list.addAll(Arrays.asList(recStrings));
			list = Controller.extendRECFunction(list);
		} else if (tag.equals("Banner")) {
			list.addAll(Arrays.asList(adsFuntionStrings));
		} else if (tag.equals("FullScreen")) {
			list.addAll(Arrays.asList(adsFuntionStrings));
		} else if (tag.equals("MoreAPP")) {
			list.addAll(Arrays.asList(adsFuntionStrings));
		} else if (tag.equals("OfferWall")) {
			list.addAll(Arrays.asList(adsFuntionStrings));
		}
		

		for (String item : list) {
			HashMap<String, String> map = new HashMap<String, String>();
			map.put("title", item);
			map.put("tag", tag);
			map.put("last", last);
			sysList.add(map);
		}
	}

	public static void showDialog(String title, String msg) {
		final String curMsg = msg;
		final String curTitle = title;

		mUIHandler.post(new Runnable() {
			@Override
			public void run() {
				new AlertDialog.Builder(mAct)
						.setTitle(curTitle)
						.setMessage(curMsg)
						.setPositiveButton("Ok",
								new DialogInterface.OnClickListener() {

									@Override
									public void onClick(DialogInterface dialog,
											int which) {

									}
								}).create().show();
			}
		});
	}

	public void showTipDialog() {

		mUIHandler.post(new Runnable() {
			@Override
			public void run() {
				new AlertDialog.Builder(mAct)
						.setTitle(R.string.paying_title)
						.setMessage(R.string.paying_message)
						.setPositiveButton("NO",
								new DialogInterface.OnClickListener() {

									@Override
									public void onClick(DialogInterface dialog,
											int which) {
										/**
										 * 重置支付状态
										 */
										wrapper.nativeResetPayState();
									}
								})
						.setNegativeButton("YES",
								new DialogInterface.OnClickListener() {

									@Override
									public void onClick(DialogInterface dialog,
											int which) {

									}
								}).create().show();
			}
		});
	}

	public static void Exit() {
		mAct.finish();
		System.exit(0);

	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		PluginWrapper.onDestroy();
		wrapper.nativeUnLoadPlugins();
	};



	@Override
	protected void onStop() {
		super.onStop();
		wrapper.nativeStopSession();
		if (!isAppOnForeground()) {
			isAppForeground = false;
		}
	}

	@Override
	protected void onResume() {
		super.onResume();
		PluginWrapper.onResume();
		wrapper.nativeStartSession();
		/**
		 * 后台切换回来判断是否支持调用暂停界面接口
		 */
		if (!isAppForeground) {
			wrapper.nativePause();
			isAppForeground = true;
		}
	}

	@Override
	public void onPause() {
		PluginWrapper.onPause();
		super.onPause();
	}
	
	 @Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		PluginWrapper.onActivityResult(requestCode, resultCode, data);
	}

	@Override
	protected void onNewIntent(Intent intent) {
		PluginWrapper.onNewIntent(intent);
		super.onNewIntent(intent);
	}

	@Override
	protected void onRestart() {
		PluginWrapper.onRestart();
		super.onRestart();
	}
	
	public boolean isAppOnForeground() {
		ActivityManager activityManager = (ActivityManager) getApplicationContext()
				.getSystemService(Context.ACTIVITY_SERVICE);
		String packageName = getApplicationContext().getPackageName();
		List<RunningAppProcessInfo> appProcesses = activityManager
				.getRunningAppProcesses();
		if (appProcesses == null)
			return false;
		for (RunningAppProcessInfo appProcess : appProcesses) {
			if (appProcess.processName.equals(packageName)
					&& appProcess.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND) {
				return true;
			}
		}
		return false;
	}

	private boolean isAppForeground = true;
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			/**
			 * 判断是否支持调用退出界面的接口
			 */
			if (wrapper.nativeUserIsFunctionSupported("exit")) {
				wrapper.nativeExit();

				return true;
			}
		}
		return super.onKeyDown(keyCode, event);
	}
	
	private static int  getResourceId(String name, String type) {
	    return mAct.getResources().getIdentifier(name, type, mAct.getPackageName());
	}
	
	private static LinearLayout myLayout;
	/**
	 * 
	* @Title: ChoosePayMode 
	* @Description: 多支付调用方法
	* @param @param payMode     
	* @return void   
	* @throws
	 */
	public static void  ChoosePayMode(ArrayList<String> payMode) {
		myLayout = new LinearLayout(mAct);
		OnClickListener onclick = new OnClickListener() { 

			@Override
			public void onClick(View v) {
				wrapper.nativePayMode((String) v.getTag());
			}
	    };
		for (int i = 0; i < payMode.size(); i++) {
			Button button = new Button(mAct);
			String res = "Channel" + payMode.get(i);
			button.setText(getResourceId(res,"string"));
			button.setOnClickListener(onclick);
			button.setTag(payMode.get(i));
			myLayout.addView(button);
		}
			
		AlertDialog.Builder dialog02 = new AlertDialog.Builder(mAct);    
	   	dialog02.setView(myLayout); 
	   	dialog02.setTitle("UI PAY");
	   	
	    	
	   	dialog02.show();
	}
	 
}
