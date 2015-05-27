#include "Ads.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include <stdlib.h>

using namespace anysdk::framework;

#define  LOG_TAG    "Ads"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);
extern "C"{
void Java_com_anysdk_sample_wrapper_nativeShowAds(JNIEnv*  env, jobject thiz)
{
	Ads::getInstance()->showAds();
}
void Java_com_anysdk_sample_wrapper_nativeHideAds(JNIEnv*  env, jobject thiz)
{
	Ads::getInstance()->hideAds();
}

void Java_com_anysdk_sample_wrapper_nativePreloadAds(JNIEnv*  env, jobject thiz)
{
	Ads::getInstance()->preloadAds();
}
}


Ads* Ads::_pInstance = NULL;

Ads::Ads()
{
	_pAds = AgentManager::getInstance()->getAdsPlugin();
	if(!_pAds) return;

	_pAds->setAdsListener(this);
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

void Ads::showAds()
{
	LOGD("showAds");
	if(!_pAds || !(_pAds->isAdTypeSupported(AD_TYPE_BANNER))) return;
	_pAds->showAds(AD_TYPE_BANNER,1);

}

void Ads::hideAds()
{
	if(!_pAds || !(_pAds->isAdTypeSupported(AD_TYPE_BANNER))) return;
	_pAds->hideAds(AD_TYPE_BANNER,1);
}
void Ads::preloadAds()
{
	if(!_pAds || !(_pAds->isAdTypeSupported(AD_TYPE_BANNER))) return;
	_pAds->preloadAds(AD_TYPE_BANNER);
}


