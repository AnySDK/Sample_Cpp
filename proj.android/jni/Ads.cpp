#include "Ads.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include <stdlib.h>
#ifndef AS_NO_USING_CPP11
#include <functional>
#endif

using namespace anysdk::framework;

#define  LOG_TAG    "Ads"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);
extern "C"{
void Java_com_anysdk_sample_wrapper_nativeShowAds(JNIEnv*  env, jobject thiz, jint type, jint index)
{
	Ads::getInstance()->showAds(type, index);
}
void Java_com_anysdk_sample_wrapper_nativeHideAds(JNIEnv*  env, jobject thiz, jint type, jint index)
{
	Ads::getInstance()->hideAds(type, index);
}

void Java_com_anysdk_sample_wrapper_nativePreloadAds(JNIEnv*  env, jobject thiz, jint type, jint index)
{
	Ads::getInstance()->preloadAds(type, index);
}

void Java_com_anysdk_sample_wrapper_nativeSpendPoints(JNIEnv*  env, jobject thiz)
{
	Ads::getInstance()->spendPoints();
}

jfloat Java_com_anysdk_sample_wrapper_nativeQueryPoints(JNIEnv*  env, jobject thiz)
{
	return (jfloat)Ads::getInstance()->queryPoints();
}
}

void adsCallback(int code,string msg)
{
	LOGD("adsCallback %d,%s",code,msg.c_str());
	switch(code)
	{
	case kAdsReceived://广告接受成功回调

		break;
	case kAdsShown://广告展示回调

		break;
	case kAdsDismissed://广告消失回调

		break;
	case kPointsSpendSucceed://积分设置成功回调

		break;
	case kPointsSpendFailed://积分设置失败回调

		break;
	case kNetworkError://网络错误回调

		break;
	case kUnknownError://未知错误回调

		break;
	case kOfferWallOnPointsChanged://积分改变回调

		break;
	default:
		break;
	}

}


Ads* Ads::_pInstance = NULL;

Ads::Ads()
{
	_pAds = AgentManager::getInstance()->getAdsPlugin();
	if(!_pAds) return;

	_pAds->setAdsListener(this);
#ifndef AS_NO_USING_CPP11
	_pAds->setCallback(adsCallback);
#endif
}

Ads::~Ads()
{

}

Ads* Ads::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new Ads();
    }
    return _pInstance;
}

void Ads::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

void Ads::onAdsResult(AdsResultCode code, const char* msg)
{
	LOGD("adsCallback %d,%s",code, msg);
	switch(code)
	{
	case kAdsReceived://广告接受成功回调

		break;
	case kAdsShown://广告展示回调

		break;
	case kAdsDismissed://广告消失回调

		break;
	case kPointsSpendSucceed://积分设置成功回调

		break;
	case kPointsSpendFailed://积分设置失败回调

		break;
	case kNetworkError://网络错误回调

		break;
	case kUnknownError://未知错误回调

		break;
	case kOfferWallOnPointsChanged://积分改变回调

		break;
	default:
		break;
	}

}


void Ads::showAds(int type,int index)
{
	LOGD("showAds");
	if(!_pAds || !(_pAds->isAdTypeSupported((AdsType)type))) return;
	_pAds->showAds((AdsType)type, index);

}

void Ads::hideAds(int type,int index)
{
	if(!_pAds || !(_pAds->isAdTypeSupported((AdsType)type))) return;
	_pAds->hideAds((AdsType)type, index);
}
void Ads::preloadAds(int type,int index)
{
	if(!_pAds || !(_pAds->isAdTypeSupported((AdsType)type))) return;
	_pAds->preloadAds((AdsType)type, index);
}

void Ads::spendPoints()
{
	if(!_pAds) return;
	_pAds->spendPoints(100);
}

float Ads::queryPoints()
{
	if(!_pAds) return -1.0;
	return _pAds->queryPoints();
}


