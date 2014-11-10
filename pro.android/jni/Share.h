#ifndef __MY_Share_H__
#define __MY_Share_H__

#include "AgentManager.h"
#include "string.h"
using namespace anysdk::framework;
using namespace std;
class Share:public ShareResultListener
{
public:
    static Share* getInstance();
    static void purge();

    //分享系统

    void setListener();

    //分享系统功能
    void share();

    //分享回调函数
    virtual void onShareResult(ShareResultCode ret, const char* msg);



private:
    	Share();
    virtual ~Share();

    static Share* _pInstance;

};

#endif
