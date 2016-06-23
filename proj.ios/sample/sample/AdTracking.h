//
//  AdTracking.h
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#ifndef __MY_ADTRACKING_H__
#define __MY_ADTRACKING_H__

#include "AgentManager.h"
#include <sstream>
using namespace std;

using namespace anysdk::framework;

class AdTracking
{
public:
    static AdTracking* getInstance();
    static void purge();
    
    void onRegister();
    
    void onLogin();
    
    void onPay();
    
    void trackEvent();
    
    void onStartToPay();
    
    void onCreateRole();
    
    void onLevelUp();
    
    bool isFunctionSupported(string functionName);
    template <class T>
    static std::string ConvertToString(T value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
    
    
private:
    AdTracking();
    virtual ~AdTracking();
    
    static AdTracking* _pInstance;
    
     ProtocolAdTracking* _pAdTracking;
    
};

#endif
