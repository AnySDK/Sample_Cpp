#ifndef __MY_Ads_H__
#define __MY_Ads_H__

#include "AgentManager.h"
#include "string.h"
using namespace anysdk::framework;
using namespace std;
class Ads:public AdsListener
{
public:
    static Ads* getInstance();
    static void purge();

    //广告系统

    //广告回调函数
    virtual void onAdsResult(AdsResultCode code, const char* msg);

    //广告系统展示
    void showAds();

    //广告系统隐藏
    void hideAds();

    //广告系统隐藏
    void preloadAds();


private:
    	Ads();
    virtual ~Ads();

    static Ads* _pInstance;

};

#endif
