#ifndef __MY_Push_H__
#define __MY_Push_H__

#include "AgentManager.h"
#include "string.h"
using namespace anysdk::framework;
using namespace std;
class Push:public PushActionListener
{
public:
    static Push* getInstance();
    static void purge();

    //推送系统

    void setListener();

    //开启推送
    void startPush();

    //开启推送
    void closePush();

    //设置别名
    void setAlias();

    //删除别名
    void delAlias();

    //设置标签
    void setTags();

    //删除标签
    void delTags();



    //Push回调函数
    virtual void onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg);



private:
    	Push();
    virtual ~Push();

    static Push* _pInstance;

};

#endif
