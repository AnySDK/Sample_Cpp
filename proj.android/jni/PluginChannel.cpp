#include "PluginChannel.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include <stdlib.h>
#include "Analytics.h"
#include "Push.h"
#ifndef AS_NO_USING_CPP11
#include <functional>
#endif

using namespace anysdk::framework;

#define  LOG_TAG    "PluginChannel"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);

void CCMessageBox(const char* content, const char* title)
{
    PluginJniMethodInfo t;
    if (PluginJniHelper::getStaticMethodInfo(t, "com/anysdk/sample/MainActivity", "showDialog", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring stringArg1;

        if (!title) {
            stringArg1 = t.env->NewStringUTF("");
        } else {
            stringArg1 = t.env->NewStringUTF(title);
        }

        jstring stringArg2 = t.env->NewStringUTF(content);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);

        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CCExit()
{
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t
		, "com/anysdk/sample/MainActivity"
		, "Exit"
		, "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ShowTipDialog()
{
    PluginJniMethodInfo t;
    if (PluginJniHelper::getStaticMethodInfo(t, "com/game/sample/MainActivity", "showTipDialog", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }


}
void userCallback(int code,string msg)
{
	LOGD("userCallback %d,%s",code,msg.c_str());
	bool _userLogined = false;
	switch(code)
	{
	case kInitSuccess://初始化SDK成功回调
		break;
	case kInitFail://初始化SDK失败回调
		CCExit();
		break;
	case kLoginSuccess://登陆成功回调
        _userLogined = true;
        CCMessageBox(msg.c_str(), "User is  online");
        if (PluginChannel::getInstance()->getChannelId() == "000255") {//UC渠道
			LOGD("开始调用submitLoginGameRole函数");
			PluginChannel::getInstance()->submitLoginGameRole();
			LOGD("结束调用submitLoginGameRole函数");
		}
        break;
	case kLoginNetworkError://登陆失败回调
    case kLoginCancel://登陆取消回调
	case kLoginFail://登陆失败回调
    	CCMessageBox(msg.c_str(), "fail");
    	_userLogined = false;
    	Analytics::getInstance()->logError("login","fail");
    	break;
	case kLogoutSuccess://登出成功回调

		break;
	case kLogoutFail://登出失败回调
		CCMessageBox(msg.c_str()  , "登出失败");
		break;
	case kPlatformEnter://平台中心进入回调
		break;
	case kPlatformBack://平台中心退出回调
		break;
	case kPausePage://暂停界面回调
		break;
	case kExitPage://退出游戏回调
            CCExit();

		break;
	case kAntiAddictionQuery://防沉迷查询回调
		CCMessageBox(msg.c_str()  , "防沉迷查询回调");
		break;
	case kRealNameRegister://实名注册回调
		CCMessageBox(msg.c_str()  , "实名注册回调");
		break;
	case kAccountSwitchSuccess://切换账号成功回调
		break;
	case kAccountSwitchFail://切换账号成功回调
		break;
	case kOpenShop://打开游戏商店回调
		break;
	default:
		break;
	}
}

void iapCallback(int code,string msg)
{
	LOGD("iapCallback %d,%s",code,msg.c_str());
	  std::string temp = "fail";
		switch(code)
		{
		case kPaySuccess://支付成功回调
			temp = "Success";
			CCMessageBox(temp.c_str() , temp.c_str() );
			break;
		case kPayFail://支付失败回调
			CCMessageBox(temp.c_str()  , temp.c_str() );
			break;
		case kPayCancel://支付取消回调
			CCMessageBox(temp.c_str()  , "Cancel" );
			break;
		case kPayNetworkError://支付超时回调
			CCMessageBox(temp.c_str()  , "NetworkError");
			break;
		case kPayProductionInforIncomplete://支付信息不完整
			CCMessageBox(temp.c_str()  , "ProductionInforIncomplete");
			break;
		/**
		 * 新增加:正在进行中回调
		 * 支付过程中若SDK没有回调结果，就认为支付正在进行中
		 * 游戏开发商可让玩家去判断是否需要等待，若不等待则进行下一次的支付
		 */
		case kPayNowPaying:
			ShowTipDialog();
			break;
		case kPayRechargeSuccess: //充值成功回调
			break;
		default:
			break;
		}


}


PluginChannel* PluginChannel::_pInstance = NULL;

PluginChannel::PluginChannel()
{
	_pUser = NULL;
	_pAgent = NULL;
	_pAnalytics = NULL;
	_pluginsIAPMap = NULL;

}

PluginChannel::~PluginChannel()
{
    //unloadPlugins();
}

PluginChannel* PluginChannel::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new PluginChannel();
    }
    return _pInstance;
}

void PluginChannel::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}



void PluginChannel::loadPlugins()
{
    LOGD("Load plugins invoked");
    /**
     * appKey、appSecret、privateKey不能使用Sample中的值，需要从打包工具中游戏管理界面获取，替换
     * oauthLoginServer参数是游戏服务提供的用来做登陆验证转发的接口地址。
     */
    std::string oauthLoginServer = "http://oauth.game.com/api/OauthLoginDemo/Login.php";
    std::string appKey = "D22AB625-CD4C-2167-D35C-C5A03E5896F5";
    std::string appSecret = "8959c650440b6b051d6af588d7f965f3";
    std::string privateKey = "BA26F2670407E0B8664DDA544026FA54";
    
	_pAgent = AgentManager::getInstance();
	_pAgent->init(appKey,appSecret,privateKey,oauthLoginServer);

    //使用框架中代理类进行插件初始化
	_pAgent->loadAllPlugins();

	do
	{
		_pUser = AgentManager::getInstance()->getUserPlugin();

		if(!_pUser) break;


		//对用户系统设置监听类
		_pUser->setActionListener(this);

#ifndef AS_NO_USING_CPP11
		_pUser->setCallback(userCallback);
		AgentManager::getInstance()->getCustomPlugin()->setCallback(userCallback);
#endif


	}while(0);

    //对支付系统设置监听类
    LOGD("Load plugins invoked");
    _pluginsIAPMap  = AgentManager::getInstance()->getIAPPlugin();
    std::map<std::string , ProtocolIAP*>::iterator iter;
    for(iter = _pluginsIAPMap->begin(); iter != _pluginsIAPMap->end(); iter++)
    {
    	(iter->second)->setResultListener(this);
#ifndef AS_NO_USING_CPP11
    	(iter->second)->setCallback(iapCallback);
#endif
    }

    do
	{
    	_pAnalytics = Analytics::getInstance();

		if(!_pAnalytics) break;
	    _pAnalytics->setCaptureUncaughtException(true);
	    _pAnalytics->setSessionContinueMillis(15000);
	    _pAnalytics->logTimedEventBegin("Load");


	}while(0);

    Push::getInstance()->startPush();

}



void PluginChannel::unloadPlugins()
{
    LOGD("Unload plugins invoked");
    _pAnalytics->logTimedEventEnd("Unload");
    _pAgent->unloadAllPlugins();

}




void PluginChannel::login()
{

	_pUser->setActionListener(this);
	if(!_pUser) return;
	_pUser->login();
	_pAnalytics->logEvent("login");
}

bool PluginChannel::isLogined()
{
	if(!_pUser) return false;

	return _pUser->isLogined();
}

void PluginChannel::logout()
{
	if(!_pUser || !isFunctionSupported("logout")) return;
	_pUser->callFuncWithParam("logout",NULL);
}

bool PluginChannel::isFunctionSupported(std::string strClassName)
{
	if(!_pUser) return false;

	return _pUser->isFunctionSupported(strClassName);
}

void ChoosePayMode(std::vector<std::string>& pluginId)
{
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
	    "com/game/sample/MainActivity",
	    "ChoosePayMode",
	     "([Ljava/lang/String;)V"))
	{
		jobjectArray ret = t.env->NewObjectArray(pluginId.size(),  t.env->FindClass("java/lang/String"), 0);
		for(int size = 0; size < pluginId.size(); size++ )
		{
			LOGD("%s",pluginId[size].c_str());
			t.env->SetObjectArrayElement(ret,size,t.env->NewStringUTF(pluginId[size].c_str()));
		}


		// invoke java method
		t.env->CallStaticVoidMethod(t.classID, t.methodID, ret);
		t.env->DeleteLocalRef(ret);
		t.env->DeleteLocalRef(t.classID);
	}
}
void PluginChannel::pay()
{

	std::map<std::string , ProtocolIAP*>::iterator it = _pluginsIAPMap->begin();
	std::string channelId = _pAgent->getChannelId();
	if(_pluginsIAPMap)
	{
		productInfo["Product_Price"] = "1";
        if(channelId=="000016" || channelId =="000009"|| channelId =="000349"){
			productInfo["Product_Id"] = "1";
		}
        else
        if(channelId=="000056" ){//联通，传计费点
        	productInfo["Product_Id"] = "130201102727";
		}
		else
		if (channelId=="000266") {//移动基地，传计费点后三位
			productInfo["Product_Id"] = "001";
		}
		else
		{
			productInfo["Product_Id"] = "monthly";
		}

		productInfo["Product_Name"] = "豌豆荚测试a1";
		productInfo["Server_Id"] = "13";
		productInfo["Product_Count"] = "1";
		productInfo["Role_Id"] = "1";
		productInfo["Role_Name"] = "1";
		productInfo["Role_Grade"] = "1";
		productInfo["Role_Balance"] = "1";
		_pAnalytics->logEvent("pay", productInfo);
		if(_pluginsIAPMap->size() == 1)
		{

			(it->second)->payForProduct(productInfo);
		}
		else if(_pluginsIAPMap->size() > 1)
		{

			std::vector<std::string> pluginId;
			int count = 0;
			for (;it != _pluginsIAPMap->end();++it)
			{
				pluginId.push_back(it->first);
			}
			ChoosePayMode(pluginId);
		}
	}

}
void PluginChannel::resetPayState()
{
	ProtocolIAP::resetPayState();
	pay();
}

std::string PluginChannel::getUserId()
{
	if(!_pUser) return "";

	return 	_pUser->getUserID();
}

void PluginChannel::payMode(std::string id)
{
	std::map<std::string , ProtocolIAP*>::iterator iter;
	iter = _pluginsIAPMap->find(id);
	if(iter != _pluginsIAPMap->end())
	{
		(iter->second)->payForProduct(productInfo);
	}
}

std::string PluginChannel::getOrderId()
{
	std::map<std::string , ProtocolIAP*>::iterator iter;
	iter = _pluginsIAPMap->begin();
	if(iter != _pluginsIAPMap->end())
	{
		return (iter->second)->getOrderId();
	}
	return "";
}



void PluginChannel::enterPlatform()
{
	if(!_pUser || !isFunctionSupported("enterPlatform")) return;

	_pUser->callFuncWithParam("enterPlatform",NULL);
}

void PluginChannel::showToolBar(ToolBarPlace place)
{
	if(!_pUser || !isFunctionSupported("showToolBar")) return;

	PluginParam paramInfo(place);
	_pUser->callFuncWithParam("showToolBar",&paramInfo,NULL);
}

void PluginChannel::hideToolBar()
{
	if(!_pUser || !isFunctionSupported("hideToolBar")) return;

	_pUser->callFuncWithParam("hideToolBar",NULL);
}

void PluginChannel::pause()
{
	if(!_pUser || !isFunctionSupported("pause")) return;

	_pUser->callFuncWithParam("pause",NULL);
}

void PluginChannel::destroy()
{
	if(!_pUser || !isFunctionSupported("destroy")) return;

	_pUser->callFuncWithParam("destroy",NULL);
}

void PluginChannel::Exit()
{
	if(!_pUser || !isFunctionSupported("exit")) return;

	_pUser->callFuncWithParam("exit",NULL);
}

void PluginChannel::antiAddictionQuery()
{
	if(!_pUser || !isFunctionSupported("antiAddictionQuery")) return;

	_pUser->callFuncWithParam("antiAddictionQuery",NULL);
}
void PluginChannel::accountSwitch()
{
	if(!_pUser || !isFunctionSupported("accountSwitch")) return;

	_pUser->callFuncWithParam("accountSwitch",NULL);
}
void PluginChannel::realNameRegister()
{
	if(!_pUser || !isFunctionSupported("realNameRegister")) return;

	_pUser->callFuncWithParam("realNameRegister",NULL);
}

void PluginChannel::submitLoginGameRole()
{
	if(!_pUser || !isFunctionSupported("submitLoginGameRole")) return;

	StringMap userInfo;
	userInfo["roleId"] = "ceshi : 123456";
	userInfo["roleName"] = "ceshi : test";
	userInfo["roleLevel"] = "ceshi : 10";
	userInfo["zoneId"] = "ceshi : 123";
	userInfo["zoneName"] = "ceshi : test";
	userInfo["dataType"] = "ceshi : 1";
	userInfo["ext"] = "ceshi : login";
	PluginParam data(userInfo);
	_pUser->callFuncWithParam("submitLoginGameRole",&data,NULL);
}



void PluginChannel::onPayResult(PayResultCode ret, const char* msg, TProductInfo info)
{
	LOGD("onPayResult%d%s",ret,msg);
	  std::string temp = "fail";
		switch(ret)
		{
		case kPaySuccess://支付成功回调
			temp = "Success";
			CCMessageBox(temp.c_str() , temp.c_str() );
			break;
		case kPayFail://支付失败回调
			CCMessageBox(temp.c_str()  , temp.c_str() );
			break;
		case kPayCancel://支付取消回调
			CCMessageBox(temp.c_str()  , "Cancel" );
			break;
		case kPayNetworkError://支付超时回调
			CCMessageBox(temp.c_str()  , "NetworkError");
			break;
		case kPayProductionInforIncomplete://支付信息不完整
			CCMessageBox(temp.c_str()  , "ProductionInforIncomplete");
			break;
		/**
		 * 新增加:正在进行中回调
		 * 支付过程中若SDK没有回调结果，就认为支付正在进行中
		 * 游戏开发商可让玩家去判断是否需要等待，若不等待则进行下一次的支付
		 */
		case kPayNowPaying:
			ShowTipDialog();
			break;
		case kPayRechargeSuccess: //充值成功回调
			break;
		default:
			break;
		}


}



void PluginChannel::onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
{
	LOGD("onActionResult%d%s",code,msg);
	bool _userLogined = false;
	switch(code)
	{
	case kInitSuccess://初始化SDK成功回调
		break;
	case kInitFail://初始化SDK失败回调
		CCExit();
		break;
	case kLoginSuccess://登陆成功回调
        _userLogined = true;
        CCMessageBox(msg, "User is  online");
        if (getChannelId() == "000255") {//UC渠道
			LOGD("开始调用submitLoginGameRole函数");
			submitLoginGameRole();
			LOGD("结束调用submitLoginGameRole函数");
		}
        break;
	case kLoginNetworkError://登陆失败回调
    case kLoginCancel://登陆取消回调
	case kLoginFail://登陆失败回调
    	CCMessageBox(msg, "fail");
    	_userLogined = false;
    	Analytics::getInstance()->logError("login","fail");
    	break;
	case kLogoutSuccess://登出成功回调

		break;
	case kLogoutFail://登出失败回调
		CCMessageBox(msg  , "登出失败");
		break;
	case kPlatformEnter://平台中心进入回调
		break;
	case kPlatformBack://平台中心退出回调
		break;
	case kPausePage://暂停界面回调
		break;
	case kExitPage://退出游戏回调
            CCExit();

		break;
	case kAntiAddictionQuery://防沉迷查询回调
		CCMessageBox(msg  , "防沉迷查询回调");
		break;
	case kRealNameRegister://实名注册回调
		CCMessageBox(msg  , "实名注册回调");
		break;
	case kAccountSwitchSuccess://切换账号成功回调
		break;
	case kAccountSwitchFail://切换账号成功回调
		break;
	case kOpenShop://打开游戏商店回调
		break;
	default:
		break;
	}

}





std::string PluginChannel::getChannelId()
{
	return _pAgent->getChannelId();
}




