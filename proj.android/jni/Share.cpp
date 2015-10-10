#include "Share.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include <stdlib.h>
#ifndef AS_NO_USING_CPP11
#include <functional>
#endif
using namespace anysdk::framework;
#define  LOG_TAG    "Share"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);
extern "C"{
void Java_com_anysdk_sample_wrapper_nativeShare(JNIEnv*  env, jobject thiz)
{
	Share::getInstance()->share();
}
}

void shareCallback(int code,string msg)
{
	LOGD("shareCallback %d -- %s",code,msg.c_str());
	switch(code)
	{
	case kShareSuccess://分享成功回调
		LOGD("onShareResult success");
		break;
	case kShareFail://分享失败回调
		LOGD("onShareResult fail");
		break;
	case kShareCancel://分享取消回调
		LOGD("onShareResult cancel");
		break;
	case kShareNetworkError://分享网络出错回调
		LOGD("onShareResult error");
		break;
	default:
		break;
	}
}

Share* Share::_pInstance = NULL;

Share::Share()
{
	_pShare = AgentManager::getInstance()->getSharePlugin();
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
	if(!_pShare) return;
	_pShare->setResultListener(this);
#ifndef AS_NO_USING_CPP11
	_pShare->setCallback(shareCallback);
#endif
}

void Share::share()
{
	if(!_pShare) return;

	std::map<std::string, std::string> info;
	 // title标题，印象笔记、邮箱、信息、微信、人人网和QQ空间使用
	info["title"] = "ShareSDK是一个神奇的SDK";
	// titleUrl是标题的网络链接，仅在人人网和QQ空间使用
	info["titleUrl"] = "http://sharesdk.cn";
	// site是分享此内容的网站名称，仅在QQ空间使用
	info["site"] = "ShareSDK";
	// siteUrl是分享此内容的网站地址，仅在QQ空间使用
	info["siteUrl"] = "http://sharesdk.cn";

	// imagePath是图片的本地路径，Linked-In以外的平台都支持此参数
	info["imagePath"] = "/sdcard/test.png";
	// imageUrl是图片的网络路径，新浪微博，人人网，QQ空间支持此字段
	info["imageUrl"] = "http://www.baidu.com/img/bdlogo.png?tn=63090008_1_hao_pg";

	// url仅在微信（包括好友和朋友圈）中使用
	info["url"] ="http://sharesdk.cn";

	// text是分享文本，所有平台都需要这个字段
	info["text"] = "ShareSDK支持如微信、新浪微博、腾讯微博等社交平台";
	 // comment是我对这条分享的评论，仅在人人网和QQ空间使用
	info["comment"] = "无";

	_pShare->share(info);

}

void Share::onShareResult(ShareResultCode ret, const char* msg)
{
	LOGD("onShareResult %d",ret);
	switch(ret)
	{
	case kShareSuccess://分享成功回调
		LOGD("onShareResult success");
		break;
	case kShareFail://分享失败回调
		LOGD("onShareResult fail");
		break;
	case kShareCancel://分享取消回调
		LOGD("onShareResult cancel");
		break;
	case kShareNetworkError://分享网络出错回调
		LOGD("onShareResult error");
		break;
	default:
		break;
	}
}


