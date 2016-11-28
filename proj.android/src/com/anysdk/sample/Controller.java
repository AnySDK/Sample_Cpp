package com.anysdk.sample;

import java.util.ArrayList;
import java.util.List;

import android.util.Log;

import com.anysdk.framework.AdsWrapper;

public class Controller {

	public static void onClick(String tag, String title) {
		if (tag.equals("user")) {
			if (title.equals("login")) {
				wrapper.nativeLogin();
			} else if (title.equals("isLogined")) {
				Log.d("isLogined", wrapper.nativeIsLogined() + "");
			} else if (title.equals("getUserID")) {
				Log.d("getUserID", wrapper.nativeGetUserId());
			} else if (title.equals("logout")) {
				// 调用登出
				wrapper.nativeLogout();
			} else if (title.equals("enterPlatform")) {
				// 调用显示平台中心
				wrapper.nativeEnterPlatform();
			} else if (title.equals("showToolBar")) {
				// 显示悬浮窗
				wrapper.nativeShowToolBar();
			} else if (title.equals("hideToolBar")) {
				// 隐藏悬浮窗
				wrapper.nativeHideToolBar();
			} else if (title.equals("accountSwitch")) {
				// 切换账号
				wrapper.nativeAccountSwitch();
			} else if (title.equals("realNameRegister")) {
				// 实名注册
				wrapper.nativeRealNameRegister();
			} else if (title.equals("antiAddictionQuery")) {
				// 防沉迷查询
				wrapper.nativeAntiAddictionQuery();
			} else if (title.equals("submitLoginGameRole")) {
				// 提交角色信息
				wrapper.nativeSubmitLoginGameRole();
			}
		} else if (tag.equals("iap")) {
			if (title.equals("payForProduct")) {
				wrapper.nativePay();
			} else if (title.equals("getOrderId")) {
				// 调用登出
				Log.d("getOrderId",wrapper.nativeGetOrderId());

			}
		} else if (tag.equals("ads")) {
			if (title.equals("queryPoints")) {
				wrapper.nativeQueryPoints();
			} else if (title.equals("spendPoints")) {
				wrapper.nativeSpendPoints();
			}
		} else if (tag.equals("share")) {
			if (title.equals("share")) {
				wrapper.nativeShare();
			}
		} else if (tag.equals("social")) {
			if (title.equals("signIn")) {
				wrapper.nativeSignIn();
			} else if (title.equals("signOut")) {
				wrapper.nativeSignOut();
			} else if (title.equals("submitScore")) {
				wrapper.nativeSubmitScore();
			} else if (title.equals("showLeaderboard")) {
				wrapper.nativeShowLeaderboard();
			} else if (title.equals("unlockAchievement")) {
				wrapper.nativeUnlockAchievement();
			} else if (title.equals("showAchievements")) {
				wrapper.nativeShowAchievements();
			}
		} else if (tag.equals("push")) {
			if (title.equals("startPush")) {
				wrapper.nativeStartPush();
			} else if (title.equals("closePush")) {
				wrapper.nativeClosePush();
			} else if (title.equals("setAlias")) {
				wrapper.nativeSetAlias();
			} else if (title.equals("delAlias")) {
				wrapper.nativeDelAlias();
			} else if (title.equals("setTags")) {
				wrapper.nativeSetTags();
			} else if (title.equals("delTags")) {
				wrapper.nativeDelTags();
			}
		} else if (tag.equals("analytics")) {
			if (title.equals("startSession")) {
				wrapper.nativeStartSession();
			} else if (title.equals("stopSession")) {
				wrapper.nativeStopSession();
			} else if (title.equals("setSessionContinueMillis")) {
				wrapper.nativeSetSessionContinueMillis();
			} else if (title.equals("logError")) {
				wrapper.nativeLogError();
			} else if (title.equals("logEvent")) {
				wrapper.nativeLogEvent();
			} else if (title.equals("logTimedEventBegin")) {
				wrapper.nativeLogTimedEventBegin();
			} else if (title.equals("logTimedEventEnd")) {
				wrapper.nativeLogTimedEventEnd();
			} else if (title.equals("setCaptureUncaughtException")) {
				wrapper.nativeSetCaptureUncaughtException();
			} else if (title.equals("setAccount")) {
				wrapper.nativeSetAccount();
			} else if (title.equals("onChargeRequest")) {
				wrapper.nativeOnChargeRequest();
			} else if (title.equals("onChargeSuccess")) {
				wrapper.nativeOnChargeSuccess();
			} else if (title.equals("onChargeFail")) {
				wrapper.nativeOnChargeFail();
			} else if (title.equals("onChargeOnlySuccess")) {
				wrapper.nativeOnChargeOnlySuccess();
			} else if (title.equals("onPurchase")) {
				wrapper.nativeOnPurchase();
			} else if (title.equals("onUse")) {
				wrapper.nativeOnUse();
			} else if (title.equals("onReward")) {
				wrapper.nativeOnReward();
			} else if (title.equals("startLevel")) {
				wrapper.nativeStartLevel();
			} else if (title.equals("finishLevel")) {
				wrapper.nativeFinishLevel();
			} else if (title.equals("failLevel")) {
				wrapper.nativeFailLevel();
			} else if (title.equals("startTask")) {
				wrapper.nativeStartTask();
			} else if (title.equals("finishTask")) {
				wrapper.nativeFinishTask();
			} else if (title.equals("failTask")) {
				wrapper.nativeFailTask();
			}
		} else if (tag.equals("rec")) {
			if (title.equals("startRecording")) {
				wrapper.nativeStartRecording();
			} else if (title.equals("stopRecording")) {
				wrapper.nativeStopRecording();
			} else if (title.equals("share")) {
				wrapper.nativeRECShare();
			} else if (title.equals("pauseRecording")) {
				wrapper.nativePauseRecording();
			} else if (title.equals("resumeRecording")) {
				wrapper.nativeResumeRecording();
			} else if (title.equals("isAvailable")) {
				Log.d("isAvailable", wrapper.nativeIsAvailable() + "");
			} else if (title.equals("showToolBar")) {
				wrapper.nativeRECShowToolBar();
			} else if (title.equals("hideToolBar")) {
				wrapper.nativeRECHideToolBar();
			} else if (title.equals("isRecording")) {
				Log.d("isRecording", wrapper.nativeIsRecording() + "");
			} else if (title.equals("showVideoCenter")) {
				wrapper.nativeShowVideoCenter();
			} else if (title.equals("enterPlatform")) {
				wrapper.nativeRECEnterPlatform();
			} else if (title.equals("setMetaData")) {
				wrapper.nativeSetMetaData();
			}
		} else if (tag.equals("crash")) {
			if (title.equals("setUserIdentifier")) {
				wrapper.nativeSetUserIdentifier();
			} else if (title.equals("reportException")) {
				wrapper.nativeReportException();
			} else if (title.equals("leaveBreadcrumb")) {
				wrapper.nativeLeaveBreadcrumb();
			}
		}else if (tag.equals("Banner")) {
			aboutAds(AdsWrapper.AD_TYPE_BANNER,title);
		}else if (tag.equals("FullScreen")) {
			aboutAds(AdsWrapper.AD_TYPE_FULLSCREEN,title);
		}else if (tag.equals("MoreAPP")) {
			aboutAds(AdsWrapper.AD_TYPE_MOREAPP,title);
		}
		else if (tag.equals("OfferWall")) {
			aboutAds(AdsWrapper.AD_TYPE_OFFERWALL,title);
		}else if (tag.equals("adtracking")) {
		    if (title.equals("onRegister")) {
                wrapper.nativeOnRegister();
            } else if (title.equals("onLogin")) {
                wrapper.nativeOnLogin();
            } else if (title.equals("onPay")) {
                wrapper.nativeOnPay();
            } else if (title.equals("trackEvent")) {
                wrapper.nativeTrackEvent();
            }else if (title.equals("onCreateRole")) {
                wrapper.nativeOnCreateRole();
            }else if (title.equals("onLevelUp")) {
                wrapper.nativeOnLevelUp();
            }else if (title.equals("onStartToPay")) {
                wrapper.nativeOnStartToPay();
            }      
		}
		
	}

	public static List<String> extendUserFunction(List<String> source) {
		if (wrapper.nativeUserIsFunctionSupported("logout")) {
			source.add("logout");
		}
		if (wrapper.nativeUserIsFunctionSupported("enterPlatform")) {
			source.add("enterPlatform");
		}
		if (wrapper.nativeUserIsFunctionSupported("showToolBar")) {
			source.add("showToolBar");
		}
		if (wrapper.nativeUserIsFunctionSupported("hideToolBar")) {
			source.add("hideToolBar");
		}
		if (wrapper.nativeUserIsFunctionSupported("accountSwitch")) {
			source.add("accountSwitch");
		}
		if (wrapper.nativeUserIsFunctionSupported("realNameRegister")) {
			source.add("realNameRegister");
		}
		if (wrapper.nativeUserIsFunctionSupported("antiAddictionQuery")) {
			source.add("antiAddictionQuery");
		}
		if (wrapper.nativeUserIsFunctionSupported("submitLoginGameRole")) {
			source.add("submitLoginGameRole");
		}
		return source;
	}

	public static List<String> extendAnalyticsFunction(List<String> source) {
		if (wrapper.nativeAnalyticsIsFunctionSupported("setAccount")) {
			source.add("setAccount");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("onChargeRequest")) {
			source.add("onChargeRequest");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("onChargeSuccess")) {
			source.add("onChargeSuccess");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("onChargeFail")) {
			source.add("onChargeFail");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("onChargeOnlySuccess")) {
			source.add("onChargeOnlySuccess");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("onPurchase")) {
			source.add("onPurchase");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("onUse")) {
			source.add("onUse");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("onReward")) {
			source.add("onReward");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("startLevel")) {
			source.add("startLevel");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("finishLevel")) {
			source.add("finishLevel");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("failLevel")) {
			source.add("failLevel");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("startTask")) {
			source.add("startTask");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("finishTask")) {
			source.add("finishTask");
		}
		if (wrapper.nativeAnalyticsIsFunctionSupported("failTask")) {
			source.add("failTask");
		}
		return source;
	}

	public static List<String> extendRECFunction(List<String> source) {
		if (wrapper.nativeRECIsFunctionSupported("pauseRecording")) {
			source.add("pauseRecording");
		}
		if (wrapper.nativeRECIsFunctionSupported("resumeRecording")) {
			source.add("resumeRecording");
		}
		if (wrapper.nativeRECIsFunctionSupported("isAvailable")) {
			source.add("isAvailable");
		}
		if (wrapper.nativeRECIsFunctionSupported("showToolBar")) {
			source.add("showToolBar");
		}
		if (wrapper.nativeRECIsFunctionSupported("hideToolBar")) {
			source.add("hideToolBar");
		}
		if (wrapper.nativeRECIsFunctionSupported("isRecording")) {
			source.add("isRecording");
		}
		if (wrapper.nativeRECIsFunctionSupported("showVideoCenter")) {
			source.add("showVideoCenter");
		}
		if (wrapper.nativeRECIsFunctionSupported("enterPlatform")) {
			source.add("enterPlatform");
		}
		if (wrapper.nativeRECIsFunctionSupported("setMetaData")) {
			source.add("setMetaData");
		}
		return source;
	}
	
	   public static List<String> extendAdTrackingFunction(List<String> source) {
	        if (wrapper.nativeAdTrackingIsFunctionSupported("onCreateRole")) {
	            source.add("onCreateRole");
	        }
	        if (wrapper.nativeAdTrackingIsFunctionSupported("onLevelUp")) {
	            source.add("onLevelUp");
	        }
	        if (wrapper.nativeAdTrackingIsFunctionSupported("onStartToPay")) {
	            source.add("onStartToPay");
	        }
	        return source;
	    }
	
	public static void aboutAds(int type, String title){
		if (title.equals("preloadAds1")) {
			wrapper.nativePreloadAds(type, 1);
		} else if (title.equals("preloadAds2")) {
			wrapper.nativePreloadAds(type, 2);
		} else if (title.equals("showAds1")) {
			wrapper.nativeShowAds(type, 1);
		} else if (title.equals("showAds2")) {
			wrapper.nativeShowAds(type, 2);
		} else if (title.equals("hideAds1")) {
			wrapper.nativeHideAds(type, 1);
		} else if (title.equals("hideAds2")) {
			wrapper.nativeHideAds(type, 2);
		}
	}

}
