//
//  REC.m
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#include "REC.h"
#include "ProtocolREC.h"
#ifndef AS_NO_USING_CPP11
#include <functional>
#endif

#define  LOG_TAG    "REC"
void recCallback(int code,string msg)
{
    printf("recCallback %d -- %s",code,msg.c_str());
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
	printf("isFunctionSupported%s:%s",strClassName.c_str(), rec->isFunctionSupported(strClassName.c_str())?"true":"false");
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
    printf("onRECResult %d\n",ret);
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
        // cocos2d::Application::getInstance()->applicationDidEnterBackground();
            break;
        case kRECShareFail://视频分享失败
            printf("kRECShareFail \n");
         //cocos2d::Application::getInstance()->applicationWillEnterForeground();
            break;
        default:
            break;
    }
    
}



