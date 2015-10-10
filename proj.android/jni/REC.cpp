//
//  REC.m
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#include "REC.h"
#include "ProtocolREC.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#ifndef AS_NO_USING_CPP11
#include <functional>
#endif
#define  LOG_TAG    "REC"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);
extern "C"{

void Java_com_anysdk_sample_wrapper_nativeStartRecording(JNIEnv*  env, jobject thiz)
{
	REC::getInstance()->startRecording();
}

void Java_com_anysdk_sample_wrapper_nativeStopRecording(JNIEnv*  env, jobject thiz)
{
	REC::getInstance()->stopRecording();
}

void Java_com_anysdk_sample_wrapper_nativeRECShare(JNIEnv*  env, jobject thiz)
{
	REC::getInstance()->share();
}

void Java_com_anysdk_sample_wrapper_nativePauseRecording(JNIEnv*  env, jobject thiz)
{
	REC::getInstance()->pauseRecording();
}

void Java_com_anysdk_sample_wrapper_nativeResumeRecording(JNIEnv*  env, jobject thiz)
{
	REC::getInstance()->resumeRecording();
}

void Java_com_anysdk_sample_wrapper_nativeRECShowToolBar(JNIEnv*  env, jobject thiz)
{
	REC::getInstance()->showToolBar();
}

void Java_com_anysdk_sample_wrapper_nativeRECHideToolBar(JNIEnv*  env, jobject thiz)
{
	REC::getInstance()->hideToolBar();
}

jboolean Java_com_anysdk_sample_wrapper_nativeIsAvailable(JNIEnv*  env, jobject thiz)
{
	return (jboolean)REC::getInstance()->isAvailable();
}

jboolean Java_com_anysdk_sample_wrapper_nativeIsRecording(JNIEnv*  env, jobject thiz)
{
	return (jboolean)REC::getInstance()->isRecording();
}

void Java_com_anysdk_sample_wrapper_nativeShowVideoCenter(JNIEnv*  env, jobject thiz)
{
	REC::getInstance()->showVideoCenter();
}

void Java_com_anysdk_sample_wrapper_nativeRECEnterPlatform(JNIEnv*  env, jobject thiz)
{
	REC::getInstance()->enterPlatform();
}

void Java_com_anysdk_sample_wrapper_nativeSetMetaData(JNIEnv*  env, jobject thiz)
{
	REC::getInstance()->setMetaData();
}

jboolean Java_com_anysdk_sample_wrapper_nativeRECIsFunctionSupported(JNIEnv*  env, jobject thiz, jstring code)
{
	std::string strClassName = PluginJniHelper::jstring2string(code);
	return (jboolean)REC::getInstance()->isFunctionSupported(strClassName);
}
}

void recCallback(int code,string msg)
{
	LOGD("recCallback %d -- %s",code,msg.c_str());
    switch(code)
    {
        case kRECInitSuccess://初始化成功
            printf("kRECInitSuccess\n");
            break;
        case kRECInitFail://初始化失败
            printf("kRECInitFail\n");
            break;
        case kRECStartRecording://开始录制
            printf("kRECStartRecording \n");
            break;
        case kRECStopRecording://结束录制
            printf("kRECStopRecording \n");
            break;
        case kRECPauseRecording://暂停录制
            printf("kRECPauseRecording \n");
            break;
        case kRECResumeRecording://恢复录制
            printf("kRECResumeRecording \n");
            break;
        case kRECShareSuccess://视频分享成功
            printf("kRECShareSuccess \n");
         //cocos2d::Application::getInstance()->applicationDidEnterBackground();
            break;
        case kRECShareFail://视频分享失败
            printf("kRECShareFail \n");
        // cocos2d::Application::getInstance()->applicationWillEnterForeground();
            break;
        default:
            break;
    }
}

REC* REC::_pInstance = NULL;

REC::REC()
{
    setListener();
}

REC::~REC()
{
    
    
}

REC* REC::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new REC();
        _pInstance->setListener();
    }
    return _pInstance;
}

void REC::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

void REC::setListener()
{
  
    ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
    if(!rec) return;
    rec->setResultListener(this);
#ifndef AS_NO_USING_CPP11
    rec->setCallback(recCallback);
#endif
}

void REC::share()
{
    ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
    if(!rec) return;
    std::map<std::string, std::string> info;
    info["Video_Desc"] = "RECSDK是一个神奇的SDK";
    info["Video_Title"] = "RECSDK";
    rec->share(info);
    
}

void REC::startRecording()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!rec) return;
	rec->startRecording();
}

void REC::stopRecording()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!rec) return;
	rec->stopRecording();
}

void REC::pauseRecording()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!isFunctionSupported("pauseRecording") || !rec) return;
	rec->callFuncWithParam("pauseRecording",NULL);
}

void REC::resumeRecording()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if( !isFunctionSupported("resumeRecording") || !rec ) return;
	rec->callFuncWithParam("resumeRecording",NULL);
}

bool REC::isAvailable()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!isFunctionSupported("isAvailable") || !rec) return false;
	return rec->callBoolFuncWithParam("isAvailable",NULL);
}

void REC::showToolBar()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!isFunctionSupported("showToolBar") || !rec) return;
	rec->callFuncWithParam("showToolBar",NULL);
}

void REC::hideToolBar()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!isFunctionSupported("hideToolBar") || !rec) return;
	rec->callFuncWithParam("hideToolBar",NULL);
}

bool REC::isRecording()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!isFunctionSupported("isRecording") || !rec ) return false;
	return rec->callBoolFuncWithParam("isRecording",NULL);
}

void REC::showVideoCenter()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!isFunctionSupported("showVideoCenter") || !rec ) return;
	rec->callFuncWithParam("showVideoCenter",NULL);
}

void REC::enterPlatform()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!isFunctionSupported("enterPlatform") || !rec) return;
	rec->callFuncWithParam("enterPlatform",NULL);
}

bool REC::isFunctionSupported(string strClassName)
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!rec) return false;
	return rec->isFunctionSupported(strClassName.c_str());
}

void REC::setMetaData()
{
	ProtocolREC * rec = AgentManager::getInstance()->getRECPlugin();
	if(!rec) return ;
	if(!isFunctionSupported("setMetaData") || !rec ) return;
	std::map<std::string, std::string> info;
	info["title"] = "RECSDK是一个神奇的SDK";
	PluginParam data(info);
	rec->callFuncWithParam("setMetaData",&data, NULL);
    
    
}

void REC::onRECResult(RECResultCode ret, const char* msg)
{
	LOGD("onRECResult %d\n",ret);
    switch(ret)
    {
        case kRECInitSuccess://初始化成功
            printf("kRECInitSuccess\n");
            break;
        case kRECInitFail://初始化失败
            printf("kRECInitFail\n");
            break;
        case kRECStartRecording://开始录制
            printf("kRECStartRecording \n");
            break;
        case kRECStopRecording://结束录制
            printf("kRECStopRecording \n");
            break;
        case kRECPauseRecording://暂停录制
            printf("kRECPauseRecording \n");
            break;
        case kRECResumeRecording://恢复录制
            printf("kRECResumeRecording \n");
            break;
        case kRECShareSuccess://视频分享成功
            printf("kRECShareSuccess \n");
         //cocos2d::Application::getInstance()->applicationDidEnterBackground();
            break;
        case kRECShareFail://视频分享失败
            printf("kRECShareFail \n");
        // cocos2d::Application::getInstance()->applicationWillEnterForeground();
            break;
        default:
            break;
    }
    
}



