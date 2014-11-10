#include "PluginChannel.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include <stdlib.h>
#include "Analytics.h"
#include "Push.h"

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


PluginChannel* PluginChannel::_pInstance = NULL;

PluginChannel::PluginChannel()
{
	_pluginsIAPMap = NULL;

}

PluginChannel::~PluginChannel()
{
    unloadPlugins();
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
    std::string oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";
	std::string appKey = "AEE563E8-C007-DC32-5535-0518D941D6C2";
	std::string appSecret = "b9fada2f86e3f73948f52d9673366610";
	std::string privateKey = "0EE38DB7E37D13EBC50E329483167860";

    AgentManager::getInstance()->init(appKey,appSecret,privateKey,oauthLoginServer);

    //使用框架中代理类进行插件初始化
    AgentManager::getInstance()->loadALLPlugin();

    //对用户系统设置监听类
    if(AgentManager::getInstance()->getUserPlugin())
    {
		AgentManager::getInstance()->getUserPlugin()->setDebugMode(true);
    	AgentManager::getInstance()->getUserPlugin()->setActionListener(this);
    }

    //对支付系统设置监听类
    LOGD("Load plugins invoked");
    _pluginsIAPMap  = AgentManager::getInstance()->getIAPPlugin();
    std::map<std::string , ProtocolIAP*>::iterator iter;
    for(iter = _pluginsIAPMap->begin(); iter != _pluginsIAPMap->end(); iter++)
    {
    	(iter->second)->setDebugMode(true);
    	(iter->second)->setResultListener(this);
    }

    Analytics::getInstance()->setCaptureUncaughtException(true);
    Analytics::getInstance()->setSessionContinueMillis(15000);
    Analytics::getInstance()->logTimedEventBegin("Load");
    Push::getInstance()->startPush();

}


void PluginChannel::unloadPlugins()
{
    LOGD("Unload plugins invoked");
    AgentManager::getInstance()->unloadALLPlugin();
    Analytics::getInstance()->logTimedEventEnd("Unload");
}




void PluginChannel::login()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		AgentManager::getInstance()->getUserPlugin()->login();
		Analytics::getInstance()->logEvent("login");
	}
}


void PluginChannel::logout()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		if(isFunctionSupported("logout"))
		{

			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("logout",NULL);
		}
	}
}

bool PluginChannel::isFunctionSupported(std::string strClassName)
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
        return AgentManager::getInstance()->getUserPlugin()->isFunctionSupported(strClassName);

	}
	return false;
}
void ChoosePayMode(std::vector<std::string>& pluginId)
{
	PluginJniMethodInfo t;
	if (PluginJniHelper::getStaticMethodInfo(t,
	    "com/anysdk/sample/MainActivity",
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
	if(_pluginsIAPMap)
	{
		productInfo["Product_Price"] = "1";
        if(AgentManager::getInstance()->getChannelId()=="000016" || AgentManager::getInstance()->getChannelId()=="000009"|| AgentManager::getInstance()->getChannelId()=="000349"){
			productInfo["Product_Id"] = "1";
		}
        else
        if(AgentManager::getInstance()->getChannelId()=="000056" ){//联通，传计费点
        	productInfo["Product_Id"] = "130201102727";
		}
		else{
			productInfo["Product_Id"] = "monthly";
		}
		productInfo["Product_Name"] = "豌豆荚测试a1";
		productInfo["Server_Id"] = "13";
		productInfo["Product_Count"] = "1";
		productInfo["Role_Id"] = "1";
		productInfo["Role_Name"] = "1";
		productInfo["Role_Grade"] = "1";
		productInfo["Role_Balance"] = "1";
		Analytics::getInstance()->logEvent("pay", productInfo);
		if(_pluginsIAPMap->size() == 1)
		{

			(it->second)->setDebugMode(true);
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
	if(AgentManager::getInstance()->getUserPlugin())
	{


		return AgentManager::getInstance()->getUserPlugin()->getUserID();
	}
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


void PluginChannel::enterPlatform()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		//使用isFunctionSupported可先判断该插件是否支持该功能
		if(isFunctionSupported("enterPlatform"))
		{
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("enterPlatform",NULL);
		}
	}
}



void PluginChannel::showToolBar(ToolBarPlace place)
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		if(isFunctionSupported("showToolBar"))
		{
			PluginParam paramInfo(place);
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("showToolBar",&paramInfo,NULL);
		}
	}



}

void PluginChannel::hideToolBar()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		if(isFunctionSupported("hideToolBar"))
		{
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("hideToolBar",NULL);
		}

	}

}

void PluginChannel::pause()
{
	if(AgentManager::getInstance()->getUserPlugin())
    {
		if(isFunctionSupported("pause"))
		{
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("pause",NULL);
		}

	}

}

void PluginChannel::destroy()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		if(isFunctionSupported("destroy"))
		{
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("destroy",NULL);
		}

	}
}

void PluginChannel::Exit()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		if(isFunctionSupported("exit"))
		{
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("exit",NULL);
		}

	}
}

void PluginChannel::antiAddictionQuery()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		if(isFunctionSupported("antiAddictionQuery"))
		{
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("antiAddictionQuery",NULL);
		}

	}

}
void PluginChannel::accountSwitch()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		if(isFunctionSupported("accountSwitch"))
		{
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("accountSwitch",NULL);
		}

	}

}
void PluginChannel::realNameRegister()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		if(isFunctionSupported("realNameRegister"))
		{
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("realNameRegister",NULL);
		}

	}

}

void PluginChannel::submitLoginGameRole()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		if(PluginChannel::getInstance()->isFunctionSupported("submitLoginGameRole"))
		{
			StringMap userInfo;
			userInfo["roleId"] = "ceshi : 123456";
			userInfo["roleName"] = "ceshi : test";
			userInfo["roleLevel"] = "ceshi : 10";
			userInfo["zoneId"] = "ceshi : 123";
			userInfo["zoneName"] = "ceshi : test";
			userInfo["dataType"] = "ceshi : 1";
			userInfo["ext"] = "ceshi : login";
			PluginParam data(userInfo);
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("submitLoginGameRole",&data,NULL);
		}
	}

}

void ShowTipDialog()
{
    PluginJniMethodInfo t;
    if (PluginJniHelper::getStaticMethodInfo(t, "com/anysdk/sample/MainActivity", "showTipDialog", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }


}

void PluginChannel::onPayResult(PayResultCode ret, const char* msg, TProductInfo info)
{
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
		case kPayProductionInforIncomplete://支付超时回调
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
	default:
		break;
	}

}





std::string PluginChannel::getChannelId()
{
	return AgentManager::getInstance()->getChannelId();
}




