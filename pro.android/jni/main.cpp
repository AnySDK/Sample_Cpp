#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include "PluginChannel.h"
#include "Analytics.h"
#include "Ads.h"
#include "Share.h"
#include "Social.h"
#include "AgentManager.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace anysdk::framework;

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    PluginJniHelper::setJavaVM(vm);  // for plugins
    return JNI_VERSION_1_4;
}

void Java_com_anysdk_sample_wrapper_nativeInitPlugins(JNIEnv*  env, jobject thiz)
{
    PluginChannel::getInstance()->loadPlugins();
}

void Java_com_anysdk_sample_wrapper_nativeUnLoadPlugins(JNIEnv*  env, jobject thiz)
{
    PluginChannel::getInstance()->unloadPlugins();
    PluginChannel::purge();
}


void Java_com_anysdk_sample_wrapper_nativeLogin(JNIEnv*  env, jobject thiz)
{
    PluginChannel::getInstance()->login();
}
void Java_com_anysdk_sample_wrapper_nativeLogout(JNIEnv*  env, jobject thiz)
{
    PluginChannel::getInstance()->logout();
}
void Java_com_anysdk_sample_wrapper_nativeAccountSwitch(JNIEnv*  env, jobject thiz)
{
    PluginChannel::getInstance()->accountSwitch();
}
void Java_com_anysdk_sample_wrapper_nativeDestroy(JNIEnv*  env, jobject thiz)
{
    PluginChannel::getInstance()->destroy();
}

void Java_com_anysdk_sample_wrapper_nativeEnterPlatform(JNIEnv*  env, jobject thiz)
{
	PluginChannel::getInstance()->enterPlatform();
}

void Java_com_anysdk_sample_wrapper_nativePay(JNIEnv*  env, jobject thiz)
{
    PluginChannel::getInstance()->pay();
}

void Java_com_anysdk_sample_wrapper_nativeResetPayState(JNIEnv*  env, jobject thiz)
{
    PluginChannel::getInstance()->resetPayState();
}

void Java_com_anysdk_sample_wrapper_nativeShowToolBar(JNIEnv*  env, jobject thiz)
{
	PluginChannel::getInstance()->showToolBar(kToolBarTopLeft);
}

void Java_com_anysdk_sample_wrapper_nativeHideToolBar(JNIEnv*  env, jobject thiz)
{
	PluginChannel::getInstance()->hideToolBar();
}

void Java_com_anysdk_sample_wrapper_nativePause(JNIEnv*  env, jobject thiz)
{
	PluginChannel::getInstance()->pause();
}

void Java_com_anysdk_sample_wrapper_nativeExit(JNIEnv*  env, jobject thiz)
{
	PluginChannel::getInstance()->Exit();
}

void Java_com_anysdk_sample_wrapper_nativeRealNameRegister(JNIEnv*  env, jobject thiz)
{
	PluginChannel::getInstance()->realNameRegister();
}

void Java_com_anysdk_sample_wrapper_nativeAntiAddictionQuery(JNIEnv*  env, jobject thiz)
{

	PluginChannel::getInstance()->antiAddictionQuery();
}

void Java_com_anysdk_sample_wrapper_nativePayMode(JNIEnv*  env, jobject thiz, jstring code)
{
	std::string strClassName = PluginJniHelper::jstring2string(code);
	PluginChannel::getInstance()->payMode(strClassName);
}




jboolean
Java_com_anysdk_sample_wrapper_nativeIsFunctionSupported(JNIEnv*  env, jobject thiz, jstring code)
{
	std::string strClassName = PluginJniHelper::jstring2string(code);
	return (jboolean)PluginChannel::getInstance()->isFunctionSupported(strClassName);
}

void
Java_com_anysdk_sample_wrapper_nativeExcuteFunction(JNIEnv*  env, jobject thiz, jstring code)
{
	std::string strClassName = PluginJniHelper::jstring2string(code);

	if (PluginChannel::getInstance()->isFunctionSupported(strClassName)) {
		AgentManager::getInstance()->getUserPlugin()->callFuncWithParam(strClassName.c_str(),NULL);
	}

}

jstring
Java_com_anysdk_sample_wrapper_nativeGetChannelId(JNIEnv*  env, jobject thiz)
{

	return env->NewStringUTF(PluginChannel::getInstance()->getChannelId().c_str());
}

jstring
Java_com_anysdk_sample_wrapper_nativeGetCustomParam(JNIEnv*  env, jobject thiz)
{

	return env->NewStringUTF(AgentManager::getInstance()->getCustomParam().c_str());
}

void Java_com_anysdk_sample_wrapper_nativeSubmitLoginGameRole(JNIEnv*  env, jobject thiz)
{
	PluginChannel::getInstance()->submitLoginGameRole();
}




}
