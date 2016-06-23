//
//  AdTracking.m
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#include "AdTracking.h"

#define  LOG_TAG    "AdTracking"

AdTracking* AdTracking::_pInstance = NULL;

AdTracking::AdTracking()
{
    _pAdTracking = AgentManager::getInstance()->getAdTrackingPlugin();

}

AdTracking::~AdTracking()
{
    
}

AdTracking* AdTracking::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new AdTracking();
    }
    return _pInstance;
}

void AdTracking::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}


void AdTracking::onRegister()
{
    if (!_pAdTracking) return;
    string userId = "userid";
    _pAdTracking->onRegister(userId.c_str());
}

void AdTracking::onLogin()
{
    if (!_pAdTracking) return;
    map<string, string> userInfo;
    userInfo["User_Id"] = "userid";
    userInfo["Role_Id"] = "roleid";
    userInfo["Role_Name"] = "rolename";
    _pAdTracking->onLogin(userInfo);
}

void AdTracking::onPay()
{
    if (!_pAdTracking) return;
    map<string, string> productInfo;
    productInfo["User_Id"] = "userid";
    productInfo["Order_Id"] = "orderid";
    productInfo["Currency_Amount"] = "5";
    productInfo["Currency_Type"] = "CNY";
    productInfo["Payment_Type"] = "paytype";
    productInfo["Payment_Time"] = "paytime";
    productInfo["Item_Id"] = "itemid";
    productInfo["Item_Count"] = "3";
    _pAdTracking->onPay(productInfo);
}

void AdTracking::trackEvent()
{
    if (!_pAdTracking) return;
    string eventId = "TEST";
    map<string, string> info;
    info["User_Id"] = "userid";
    _pAdTracking->trackEvent(eventId.c_str(), &info);
    _pAdTracking->trackEvent("event_1");
    _pAdTracking->trackEvent("event_2");
    _pAdTracking->trackEvent("onCustEvent1");
    _pAdTracking->trackEvent("onCustEvent2");
}

void AdTracking::onStartToPay()
{
    if (!_pAdTracking || !isFunctionSupported("onStartToPay")) return;
    map<string, string> info;
    info["User_Id"] = "userid";
    info["Order_Id"] = "orderid";
    info["Currency_Amount"] = "5";
    info["Currency_Type"] = "CNY";
    info["Payment_Type"] = "paytype";
    info["Payment_Time"] = "paytime";
    info["Item_Id"] = "itemid";
    info["Item_Count"] = "3";
    _pAdTracking->trackEvent("onStartToPay",&info);
//    PluginParam data(info);
//    _pAdTracking->callFuncWithParam("onStartToPay", &data, NULL);
}

void AdTracking::onCreateRole()
{
    if (!_pAdTracking || !isFunctionSupported("onCreateRole")) return;
    map<string, string> info;
    info["User_Id"] = "userid";
    info["Role_Id"] = "roleid";
    info["Role_Name"] = "rolename";
    _pAdTracking->trackEvent("onCreateRole",&info);

//    PluginParam data(info);
//    _pAdTracking->callFuncWithParam("onCreateRole", &data, NULL);
}

void AdTracking::onLevelUp()
{
    if (!_pAdTracking || !isFunctionSupported("onLevelUp")) return;
    map<string, string> info;
    info["User_Id"] = "userid";
    info["Role_Id"] = "roleid";
    info["Role_Name"] = "rolename";
    info["Level"] = "4";

    _pAdTracking->trackEvent("onLevelUp",&info);
//    PluginParam data(info);
//    _pAdTracking->callFuncWithParam("onLevelUp", &data, NULL);
}



bool AdTracking::isFunctionSupported(string functionName)
{
    if (!_pAdTracking) return false;
    printf("isFunctionSupported %d\n",_pAdTracking->isFunctionSupported(functionName));
    return _pAdTracking->isFunctionSupported(functionName);
}

