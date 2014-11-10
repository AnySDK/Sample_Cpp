package com.anysdk.sample;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;


import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.protocol.HTTP;
import org.apache.http.util.EntityUtils;

import com.anysdk.framework.PluginWrapper;
import com.anysdk.sample.wrapper;



import android.R.bool;
import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.app.ActivityManager;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;
import android.widget.AbsoluteLayout;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Toast;

public class MainActivity extends Activity   implements OnClickListener{

	static {
		System.loadLibrary("game");
	}
	private static Activity mAct = null;
	private static Handler mUIHandler = null;
	private static boolean mFirst = false;
	private static Dialog myDialog = null;
	private final static String nd91Channle = "000007";

	public static boolean isFirstBegin() {
        Log.d("PluginDemo", "Is first begin : " + mFirst);
        return mFirst;
    }
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		PluginWrapper.init(this);
        wrapper.nativeInitPlugins();
        
		setContentView(R.layout.activity_main);
		mAct = this;
        mUIHandler = new Handler();

        

        Button btnUser = (Button) this.findViewById(R.id.userSystem);
        btnUser.setOnClickListener(this);


        Button btnIAP = (Button) this.findViewById(R.id.iapSystem);
        btnIAP.setOnClickListener(this);
        
        Button btnShare = (Button) this.findViewById(R.id.shareSystem);
        btnShare.setOnClickListener(this);
        
        Button btnAds = (Button) this.findViewById(R.id.adsSystem);
        btnAds.setOnClickListener(this);
        
        Button btnSocial = (Button) this.findViewById(R.id.socialSystem);
        btnSocial.setOnClickListener(this);
        
        Button btnPush = (Button) this.findViewById(R.id.pushSystem);
        btnPush.setOnClickListener(this);

        LinearLayout main = (LinearLayout) this.findViewById(R.id.main);
       
        if (wrapper.nativeGetChannelId().equals(nd91Channle)) {
        	Button shop = new Button(this);
        	shop.setOnClickListener(this);
        	shop.setTag(nd91Channle);
        	shop.setText("91 shop");
        	main.addView(shop);
		}
        Log.d("AnySDK", wrapper.nativeGetCustomParam());
        
        if (wrapper.nativeGetChannelId().equals("000266")) {//移动基地
        	Button showFloatWindow = new Button(this);
        	showFloatWindow.setOnClickListener(this);
        	showFloatWindow.setTag("showFloatWindow");
        	showFloatWindow.setText("showFloatWindow");
        	main.addView(showFloatWindow);
		}
        if (wrapper.nativeGetChannelId().equals("000266")) {//移动基地
        	Button dismissFloatWindow = new Button(this);
        	dismissFloatWindow.setOnClickListener(this);
        	dismissFloatWindow.setTag("dismissFloatWindow");
        	dismissFloatWindow.setText("dismissFloatWindow");
        	main.addView(dismissFloatWindow);
        }
    	
    	
    	
    	
    	
	}

	@Override
	public void onClick(View arg0) {

		switch (arg0.getId()) {	
	    case R.id.userSystem:
	    	showUserAction();
	        break;
	    case R.id.iapSystem:
	    	showPayAction();
	        break;
	    case R.id.shareSystem:
	    	showShareAction();
	        break;
	    case R.id.adsSystem:
	    	showAdsAction();
	        break;
	    case R.id.socialSystem:
	    	showSocialAction();
	        break;
	    case R.id.pushSystem:
	    	showPushAction();
	        break;
	    case R.id.login:
	    	wrapper.nativeLogin();
	    	myDialog.dismiss();
	        break;
	    case R.id.pay:
	    	wrapper.nativePay();
	    	myDialog.dismiss();
	        break;
	    case R.id.share:
	    	wrapper.nativeShare();
	    	myDialog.dismiss();
	        break;
	    case R.id.show:
	    	wrapper.nativeShowAds();
	    	myDialog.dismiss();
	        break;
	    case R.id.hide:
	    	wrapper.nativeHideAds();
	    	myDialog.dismiss();
	        break;
	    case R.id.submitScore:
	    	wrapper.nativeSubmitScore();
	    	myDialog.dismiss();
	        break;
	    case R.id.showLeaderboard:
	    	wrapper.nativeShowLeaderboard();
	    	myDialog.dismiss();
	        break;
	    case R.id.unlockAchievement:
	    	wrapper.nativeUnlockAchievement();
	    	myDialog.dismiss();
	        break;
	    case R.id.showAchievements:
	    	wrapper.nativeShowAchievements();
	    	myDialog.dismiss();
	        break;
	    case R.id.closePush:
	    	wrapper.nativeClosePush();
	    	myDialog.dismiss();
	        break;
	    case R.id.setAlias:
	    	wrapper.nativeSetAlias();
	    	myDialog.dismiss();
	        break;
	    case R.id.delAlias:
	    	wrapper.nativeDelAlias();
	    	myDialog.dismiss();
	        break;
	    case R.id.setTags:
	    	wrapper.nativeSetTags();
	    	myDialog.dismiss();
	        break;
	    case R.id.delTags:
	    	wrapper.nativeDelTags();
	    	myDialog.dismiss();
	        break;
	    default:
	    	if (myDialog != null) {
	    		myDialog.dismiss();
			}
	    	
	    	if (arg0.getTag().equals("logout")) {
				wrapper.nativeLogout();
			}
		    else if (arg0.getTag().equals("enterPlatform")) {
		    	wrapper.nativeEnterPlatform();
			}
		    else if (arg0.getTag().equals("showToolBar")) {
		    	wrapper.nativeShowToolBar();
			}
		    else if (arg0.getTag().equals("hideToolBar")) {
		    	wrapper.nativeHideToolBar();
			}
		    else if (arg0.getTag().equals("accountSwitch")) {
		    	wrapper.nativeAccountSwitch();
			}
		    else if (arg0.getTag().equals("realNameRegister")) {
		    	wrapper.nativeRealNameRegister();
			}
		    else if (arg0.getTag().equals("antiAddictionQuery")) {
		    	wrapper.nativeAntiAddictionQuery();
			}
		    else if (arg0.getTag().equals("submitLoginGameRole")) {
		    	wrapper.nativeSubmitLoginGameRole();
			}
		    else if (arg0.getTag().equals(nd91Channle)) {
		    	showDialog("91 shop", "91 shop");
			}
		    else if (arg0.getTag().equals("showFloatWindow")) {
		    	if (wrapper.nativeIsFunctionSupported("showFloatWindow")) {
					wrapper.nativeExcuteFunction("showFloatWindow");
				}
		    }
		    else if (arg0.getTag().equals("dismissFloatWindow")) {
		    	if (wrapper.nativeIsFunctionSupported("dismissFloatWindow")) {
					wrapper.nativeExcuteFunction("dismissFloatWindow");
				}
		    }
		    else if (arg0.getTag().equals("isMusicEnabled")) {
		    	if (wrapper.nativeIsFunctionSupported("isMusicEnabled")) {
		    		wrapper.nativeExcuteFunction("isMusicEnabled");
		    	}
		    }
	    	
	        break;
	       
	    }
	
	}
	
	 @Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		
		super.onActivityResult(requestCode, resultCode, data);
		PluginWrapper.onActivityResult(requestCode, resultCode, data);
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
	                            public void onClick(DialogInterface dialog, int which) {
	                                
	                            }
	                        }).create().show();
	            }
	        });
	    }
	public static void showTipDialog() {
        
        mUIHandler.post(new Runnable() {
            @Override
            public void run() {
                new AlertDialog.Builder(mAct)
                .setTitle(R.string.paying_title)
                .setMessage(R.string.paying_message)
                .setPositiveButton("NO", 
                        new DialogInterface.OnClickListener() {
                            
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                wrapper.nativeResetPayState();
                            }
                        })
                .setNegativeButton("YES", 
                        new DialogInterface.OnClickListener() {
                            
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                
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
	     wrapper.nativeDestroy();
	     wrapper.nativeUnLoadPlugins();
	 };
	 
	 @Override
	protected void onNewIntent(Intent intent) {
		 PluginWrapper.onNewIntent(intent);
		super.onNewIntent(intent);
	}

	public boolean isAppOnForeground() {
			ActivityManager activityManager = (ActivityManager) getApplicationContext()
					.getSystemService(Context.ACTIVITY_SERVICE);
			String packageName = getApplicationContext().getPackageName();
			List<RunningAppProcessInfo> appProcesses = activityManager.getRunningAppProcesses();
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
	protected void onStop() {
		 
		 super.onStop();
		 wrapper.nativeStopSession();
		if(!isAppOnForeground()){
			isAppForeground = false;
		}
	}	
	 
	@Override
	protected void onResume() {
		PluginWrapper.onResume();
		super.onResume();
		wrapper.nativeStartSession();
		if(!isAppForeground){
			wrapper.nativePause();
			isAppForeground = true;			
		}
	}
	@Override
	public void onPause()
	{
		PluginWrapper.onPause();
		super.onPause();
		
	}
	
	
	
		
		

		
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		
		if(keyCode == KeyEvent.KEYCODE_BACK){

			if (wrapper.nativeIsFunctionSupported("exit")) {
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
	public static void  ChoosePayMode(String[] payMode) {
		myLayout = new LinearLayout(mAct);
		OnClickListener onclick = new OnClickListener() { 

			@Override
			public void onClick(View v) {
				
				wrapper.nativePayMode((String) v.getTag());
			}
	    };
		for (int i = 0; i < payMode.length; i++) {
			Button button = new Button(mAct);
			String res = "Channel" + payMode[i];
			button.setText(getResourceId(res,"string"));
			button.setOnClickListener(onclick);
			button.setTag(payMode[i]);
			myLayout.addView(button);
		}
			
		AlertDialog.Builder dialog02 = new AlertDialog.Builder(mAct);    
	   	dialog02.setView(myLayout); 
	   	dialog02.setTitle("UI PAY");
	   	
	    	
	   	dialog02.show();
	}
	 private void showUserAction() {
	        AlertDialog.Builder builder = new AlertDialog.Builder(this);
	        View view = View.inflate(this, R.layout.activity_user, null);
	        LinearLayout user = (LinearLayout) view.findViewById(R.id.user);
	        if(wrapper.nativeIsFunctionSupported("logout"))
	        {
	        	Button logoutButton = new Button(this);
	        	logoutButton.setOnClickListener(this);
	        	logoutButton.setTag("logout");
	        	logoutButton.setText("logout");
	        	user.addView(logoutButton);
	        	//this.addContentView(logoutButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        if(wrapper.nativeIsFunctionSupported("enterPlatform"))
	        {
	        	Button enterPlatformButton = new Button(this);
	        	enterPlatformButton.setOnClickListener(this);
	        	enterPlatformButton.setTag("enterPlatform");
	        	enterPlatformButton.setText("enterPlatform");
	        	user.addView(enterPlatformButton);
	        	//this.addContentView(enterPlatformButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        if(wrapper.nativeIsFunctionSupported("showToolBar"))
	        {
	        	Button showToolBarButton = new Button(this);
	        	showToolBarButton.setOnClickListener(this);
	        	showToolBarButton.setTag("showToolBar");
	        	showToolBarButton.setText("showToolBar");
	        	user.addView(showToolBarButton);
	        	//this.addContentView(showToolBarButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        if(wrapper.nativeIsFunctionSupported("hideToolBar"))
	        {
	        	Button hideToolBarButton = new Button(this);
	        	hideToolBarButton.setOnClickListener(this);
	        	hideToolBarButton.setTag("hideToolBar");
	        	hideToolBarButton.setText("hideToolBar");
	        	user.addView(hideToolBarButton);
	        	//this.addContentView(hideToolBarButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        if(wrapper.nativeIsFunctionSupported("accountSwitch"))
	        {
	        	Button accoutSwitchButton = new Button(this);
	        	accoutSwitchButton.setOnClickListener(this);
	        	accoutSwitchButton.setTag("accountSwitch");
	        	accoutSwitchButton.setText("accountSwitch");
	        	user.addView(accoutSwitchButton);
	        	//this.addContentView(accoutSwitchButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        if(wrapper.nativeIsFunctionSupported("realNameRegister"))
	        {
	        	Button realNameRegisterButton = new Button(this);
	        	realNameRegisterButton.setOnClickListener(this);
	        	realNameRegisterButton.setTag("realNameRegister");
	        	realNameRegisterButton.setText("realNameRegister");
	        	user.addView(realNameRegisterButton);
	        	//this.addContentView(realNameRegisterButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        if(wrapper.nativeIsFunctionSupported("antiAddictionQuery"))
	        {
	        	Button antiAddictionQueryButton = new Button(this);
	        	antiAddictionQueryButton.setOnClickListener(this);
	        	antiAddictionQueryButton.setTag("antiAddictionQuery");
	        	antiAddictionQueryButton.setText("antiAddictionQuery");
	        	user.addView(antiAddictionQueryButton);
	        	//this.addContentView(antiAddictionQueryButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        
	        if(wrapper.nativeIsFunctionSupported("submitLoginGameRole"))
	        {
	        	Button submitLoginGameRoleButton = new Button(this);
	        	submitLoginGameRoleButton.setOnClickListener(this);
	        	submitLoginGameRoleButton.setTag("submitLoginGameRole");
	        	submitLoginGameRoleButton.setText("submitLoginGameRole");
	        	user.addView(submitLoginGameRoleButton);
	        	//this.addContentView(antiAddictionQueryButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        
	        if(wrapper.nativeIsFunctionSupported("isMusicEnabled"))
	        {
	        	Button isMusicEnabled = new Button(this);
	        	isMusicEnabled.setOnClickListener(this);
	        	isMusicEnabled.setTag("isMusicEnabled");
	        	isMusicEnabled.setText("isMusicEnabled");
	        	user.addView(isMusicEnabled);
	        	//this.addContentView(antiAddictionQueryButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        if(wrapper.nativeIsFunctionSupported("showFloatWindow"))
	        {
	        	Button showFloatWindow = new Button(this);
	        	showFloatWindow.setOnClickListener(this);
	        	showFloatWindow.setTag("showFloatWindow");
	        	showFloatWindow.setText("showFloatWindow");
	        	user.addView(showFloatWindow);
	        	//this.addContentView(antiAddictionQueryButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        if(wrapper.nativeIsFunctionSupported("dismissFloatWindow"))
	        {
	        	Button dismissFloatWindow = new Button(this);
	        	dismissFloatWindow.setOnClickListener(this);
	        	dismissFloatWindow.setTag("dismissFloatWindow");
	        	dismissFloatWindow.setText("dismissFloatWindow");
	        	user.addView(dismissFloatWindow);
	        	//this.addContentView(antiAddictionQueryButton, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
	        }
	        
	        
	        myDialog = builder.setView(view).create();

	        myDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
	        myDialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
	        myDialog.show();
	        


	        Button btnUser = (Button) view.findViewById(R.id.login);
	        btnUser.setOnClickListener(this);
	    }
	 
	 private void showPayAction() {
	        AlertDialog.Builder builder = new AlertDialog.Builder(this);
	        View view = View.inflate(this, R.layout.activity_iap, null);
	        myDialog = builder.setView(view).create();

	        myDialog.show();
	        myDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);

	        Button btnPay = (Button) myDialog.findViewById(R.id.pay);
	        btnPay.setOnClickListener(this);
	    }
	 
	 private void showShareAction() {
	        AlertDialog.Builder builder = new AlertDialog.Builder(this);
	        View view = View.inflate(this, R.layout.activity_share, null);
	        myDialog = builder.setView(view).create();

	        myDialog.show();
	        myDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);

	        Button btnShare = (Button) myDialog.findViewById(R.id.share);
	        btnShare.setOnClickListener(this);
	    }
	 
	 private void showAdsAction() {
	        AlertDialog.Builder builder = new AlertDialog.Builder(this);
	        View view = View.inflate(this, R.layout.activity_ads, null);
	        myDialog = builder.setView(view).create();

	        myDialog.show();
	        myDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);

	        Button btnShow = (Button) myDialog.findViewById(R.id.show);
	        btnShow.setOnClickListener(this);
	        
	        Button btnhide= (Button) myDialog.findViewById(R.id.hide);
	        btnhide.setOnClickListener(this);
	    }
	 
	 private void showSocialAction() {
	        AlertDialog.Builder builder = new AlertDialog.Builder(this);
	        View view = View.inflate(this, R.layout.activity_social, null);
	        myDialog = builder.setView(view).create();

	        myDialog.show();
	        myDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);

	        Button btnSubmitScore = (Button) myDialog.findViewById(R.id.submitScore);
	        btnSubmitScore.setOnClickListener(this);
	        
	        Button btnPay = (Button) myDialog.findViewById(R.id.showLeaderboard);
	        btnPay.setOnClickListener(this);
	        
	        Button btnUnlockAchievement = (Button) myDialog.findViewById(R.id.unlockAchievement);
	        btnUnlockAchievement.setOnClickListener(this);
	        
	        Button btnShowAchievements = (Button) myDialog.findViewById(R.id.showAchievements);
	        btnShowAchievements.setOnClickListener(this);
	    }
	 
	 private void showPushAction() {
	        AlertDialog.Builder builder = new AlertDialog.Builder(this);
	        View view = View.inflate(this, R.layout.activity_push, null);
	        myDialog = builder.setView(view).create();

	        myDialog.show();
	        myDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);

	        Button btnStopPush = (Button) myDialog.findViewById(R.id.closePush);
	        btnStopPush.setOnClickListener(this);
	        
	        Button btnSetAlias = (Button) myDialog.findViewById(R.id.setAlias);
	        btnSetAlias.setOnClickListener(this);
	        
	        Button btnDelAlias = (Button) myDialog.findViewById(R.id.delAlias);
	        btnDelAlias.setOnClickListener(this);
	        
	        Button btnSetTags = (Button) myDialog.findViewById(R.id.setTags);
	        btnSetTags.setOnClickListener(this);
	        
	        Button btnDelTags = (Button) myDialog.findViewById(R.id.delTags);
	        btnDelTags.setOnClickListener(this);
	    }

	 
	 
}
