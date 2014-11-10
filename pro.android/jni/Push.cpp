#include "Push.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include <stdlib.h>

using namespace anysdk::framework;

#define  LOG_TAG    "Push"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);

extern "C"{
void Java_com_anysdk_sample_wrapper_nativeStartPush(JNIEnv*  env, jobject thiz)
{
	Push::getInstance()->startPush();
}

void Java_com_anysdk_sample_wrapper_nativeClosePush(JNIEnv*  env, jobject thiz)
{
	Push::getInstance()->closePush();
}

void Java_com_anysdk_sample_wrapper_nativeSetAlias(JNIEnv*  env, jobject thiz)
{
	Push::getInstance()->setAlias();
}

void Java_com_anysdk_sample_wrapper_nativeDelAlias(JNIEnv*  env, jobject thiz)
{
	Push::getInstance()->delAlias();
}

void Java_com_anysdk_sample_wrapper_nativeSetTags(JNIEnv*  env, jobject thiz)
{
	Push::getInstance()->setTags();
}
void Java_com_anysdk_sample_wrapper_nativeDelTags(JNIEnv*  env, jobject thiz)
{
	Push::getInstance()->delTags();
}
}

Push* Push::_pInstance = NULL;

Push::Push()
{
	setListener();

}

Push::~Push()
{

}

Push* Push::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new Push();
    }
    return _pInstance;
}

void Push::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

void Push::setListener()
{

    if(AgentManager::getInstance()->getPushPlugin())
    {
        AgentManager::getInstance()->getPushPlugin()->setActionListener(this);
    }

}

//开启推送
void Push::startPush()
{
	 if(AgentManager::getInstance()->getPushPlugin())
	 {
	     AgentManager::getInstance()->getPushPlugin()->startPush();
	 }
}

//开启推送
void Push::closePush()
{
	 if(AgentManager::getInstance()->getPushPlugin())
	 {
		 AgentManager::getInstance()->getPushPlugin()->closePush();
	 }

}

//设置别名
void Push::setAlias()
{
	if(AgentManager::getInstance()->getPushPlugin())
	{
		AgentManager::getInstance()->getPushPlugin()->setAlias("AnySDK");
	}


}



//删除别名
void Push::delAlias()
{
	if(AgentManager::getInstance()->getPushPlugin())
	{
		AgentManager::getInstance()->getPushPlugin()->delAlias("AnySDK");
	}

}

//设置标签
void Push::setTags()
{
	if(AgentManager::getInstance()->getPushPlugin())
	{
		list<string> tags;
		tags.push_back("easy");
		tags.push_back("fast");
		AgentManager::getInstance()->getPushPlugin()->setTags(tags);
	}

}

//删除标签
void Push::delTags()
{
	if(AgentManager::getInstance()->getPushPlugin())
	{
		list<string> tags;
		tags.push_back("easy");
		tags.push_back("fast");
		AgentManager::getInstance()->getPushPlugin()->delTags(tags);
	}

}



//Push回调函数
void Push::onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg)
{
	LOGD("Push::onActionResult");
	switch(code)
	{
	case kPushReceiveMessage://Push接受到消息回调
		LOGD("%s",msg);
		break;
	default:
		break;
	}

}


