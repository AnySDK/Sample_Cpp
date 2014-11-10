#include "Share.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include <stdlib.h>

using namespace anysdk::framework;

#define  LOG_TAG    "Share"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);
extern "C"{
void Java_com_anysdk_sample_wrapper_nativeShare(JNIEnv*  env, jobject thiz)
{
	Share::getInstance()->share();
}
}

Share* Share::_pInstance = NULL;

Share::Share()
{
	setListener();
}

Share::~Share()
{


}

Share* Share::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new Share();
    }
    return _pInstance;
}

void Share::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

void Share::setListener()
{

    if(AgentManager::getInstance()->getSharePlugin())
    {
        AgentManager::getInstance()->getSharePlugin()->setResultListener(this);
    }

}

void Share::share()
{
	if(AgentManager::getInstance()->getSharePlugin())
		{

			std::map<std::string, std::string> info;
			info["title"] = "ShareSDK是一个神奇的SDK";
			info["titleUrl"] = "http://sharesdk.cn";
			info["site"] = "ShareSDK";
			info["siteUrl"] = "http://sharesdk.cn";
			info["text"] = "ShareSDK支持如微信、新浪微博、腾讯微博等社交平台";
			info["comment"] = "无";
			AgentManager::getInstance()->getSharePlugin()->share(info);
		}

}

void Share::onShareResult(ShareResultCode ret, const char* msg)
{
		switch(ret)
		{
		case kShareSuccess://分享成功回调

			break;
		case kShareFail://分享失败回调

			break;
		case kShareCancel://分享取消回调

			break;
		case kShareNetworkError://分享网络出错回调

			break;
		default:
			break;
		}

}


