#ifndef __MY_PURCHASE_H__
#define __MY_PURCHASE_H__

#include "AgentManager.h"
#include "string.h"
#include "Analytics.h"
using namespace anysdk::framework;
using namespace std;
class PluginChannel:public PayResultListener, public UserActionListener
{
public:
    static PluginChannel* getInstance();
    static void purge();

    //载入插件，同时进行插件的初始化
       void loadPlugins();

   	//卸载插件
   	void unloadPlugins();

   	//用户系统功能
   	//当前插件id
    string getPluginId();

   	//该方法是否支持:(login、getUserId为默认，可无需判断)
    bool isFunctionSupported(string strClassName);

   	//登陆
    void login();

    //登出
    void logout();


   	//获取用户唯一标识符，进行游戏端登陆
    std::string getUserId();


   	//进入渠道用户中心
    void enterPlatform();

    //显示悬浮按钮
    void showToolBar(ToolBarPlace place);

   	//隐藏悬浮按钮
    void hideToolBar();

   	//渠道退出界面调用
    void Exit();

    //sdk退出
    void destroy();

   	//渠道暂停界面调用
    void pause();

   	//切换账号
   	void accountSwitch();

   	//用户实名注册(360特有函数)
    void realNameRegister();

   	//防沉迷(360特有函数)
    void antiAddictionQuery();
    //UC提交角色信息(UC特有函数)
    void submitLoginGameRole();

   	//支付系统功能
    void pay();
    void resetPayState();











   	//支付回调函数
    virtual void onPayResult(PayResultCode ret, const char* msg, TProductInfo info);

   	//登陆回调函数
    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg);





    void payMode(std::string id);

    //获取渠道id
    std::string getChannelId();



private:
    PluginChannel();
    virtual ~PluginChannel();

    static PluginChannel* _pInstance;
	std::map<std::string, std::string> productInfo;
	std::map<std::string , ProtocolIAP*>* _pluginsIAPMap;
	ProtocolUser* _pUser;
	AgentManager* _pAgent;
	Analytics* _pAnalytics;

};

#endif
