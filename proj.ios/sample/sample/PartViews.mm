//
//  PartViews.m
//  sample
//
//  Created by cocos2dx on 14-10-29.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#import "PartViews.h"
#import "ViewController.h"
//#import "AgentManager.h"
#import "BButton.h"

#import "Ads.h"
#import "Push.h"
#import "Share.h"
#import "Social.h"
#import "Analytics.h"
#import "Crash.h"
#import "REC.h"
#import "AdTracking.h"
#import "PluginChannel.h"

#include <list>

using namespace anysdk::framework;

@implementation PartViews

static std::string user_menu[] = {"login", "logout", "enterPlatform", "showToolbar", "hideToolbar", "accountSwitch", "realNameRegister", "antiAddictionQuery", "submitLoginGameRole"};
static int user_count = sizeof(user_menu) / sizeof(user_menu[0]);

static std::string ads_menu[] = {"banner", "fullscreen", "moreapp", "offerwall"};
static int ads_count = sizeof(ads_menu) / sizeof(ads_menu[0]);

static std::string banner_menu[] = {"show banner 1", "hide banner 1", "show banner 2", "hide banner 2", "show banner 3", "hide banner 3", "show banner 4", "hide banner 4", "show banner 5", "hide banner 5"};
static int banner_count = sizeof(banner_menu) / sizeof(banner_menu[0]);

static std::string fullscreen_menu[] = {"show screen 1", "hide screen 1", "show screen 2", "hide screen 2", "show screen 3", "hide screen 3"};
static int fullscreen_count = sizeof(fullscreen_menu) / sizeof(fullscreen_menu[0]);

static std::string moreapp_menu[] = {"show moreapp 1", "hide moreapp 1", "show moreapp 2", "hide moreapp 2", "show moreapp 3", "hide moreapp 3"};
static int moreapp_count = sizeof(moreapp_menu) / sizeof(moreapp_menu[0]);

static std::string offerwall_menu[] = {"show offerwall 1", "hide offerwall 1", "show offerwall 2", "hide offerwall 2", "show offerwall 3", "hide offerwall 3"};
static int offerwall_count = sizeof(offerwall_menu) / sizeof(offerwall_menu[0]);

static std::string analytics_menu[]= {"log event", "log error"};
static int analytics_count = sizeof(analytics_menu) / sizeof(analytics_menu[0]);

static std::string share_menu[]= {"share"};
static int share_count = sizeof(share_menu) / sizeof(share_menu[0]);

static std::string iap_menu[]= {"iap pay", "iap request"};
static int iap_count = sizeof(iap_menu) / sizeof(iap_menu[0]);

static std::string push_menu[]= {"start push", "stop push", "set alias", "del alias", "set tags", "del tags"};
static int push_count = sizeof(push_menu) / sizeof(push_menu[0]);

static std::string social_menu[]= {"submit score", "show leaderboard", "unlock achievement", "show achievements"};
static int social_count = sizeof(social_menu) / sizeof(social_menu[0]);


static std::string rec_menu[]= {"start record", "stop record", "share", "pause Record", "resume Record", "showToolBar" , "hideToolBar" ,"showVideoCenter", "enterPlatform"};
static int rec_count = sizeof(rec_menu) / sizeof(rec_menu[0]);

static std::string crash_menu[]= {"setUserIdentifier", "reportException", "leaveBreadcrumb"};
static int crash_count = sizeof(crash_menu) / sizeof(crash_menu[0]);


static std::string adtracking_menu[]= {"onRegister", "onLogin", "onPay", "trackEvent", "onStartToPay", "onCreateRole", "onLevelUp"};
static int adtracking_count = sizeof(adtracking_menu) / sizeof(adtracking_menu[0]);

#define SPACE_H 0.5

typedef std::list<UIView*> LIST_VIEW;
LIST_VIEW _views;
static PartViews* _instance = nil;
static ViewController* _mianCtrl = nil;
static UIButton* backBtn = nil;
+(PartViews*)getInstance:(ViewController*)ctrl
{
    if (_instance == nil) {
        _instance = [[PartViews alloc] init];
        _mianCtrl = ctrl;
        backBtn = [_instance addOneButton:BACK_BUTTON title:@"return" sel:@selector(onClick:) rect:CGRectMake(0, 0, [ViewController getButtonSize].width, [ViewController getButtonSize].height)];
        [backBtn setHidden:true];
    }
    return _instance;
}

-(void)initAgent
{
    PluginChannel::getInstance()->loadPlugins();
}

+(int)getBaseFullscreenY
{
    return BASE_FULLSCREEN_Y;
}
+(void)setBaseFullscreenY:(int)posY
{
    BASE_FULLSCREEN_Y = posY;
}

-(void)switchView:(int)idx
{
    [self hideCurView];
    switch (idx) {
        case USER_SYSTEM:
            [self addCurrentView:user_count level:USER_LEVEL menus:user_menu];
            break;
        case IAP_SYSTEM:
            [self addCurrentView:iap_count level:IAP_LEVEL menus:iap_menu];
            break;
        case SHARE_SYSTEM:
            [self addCurrentView:share_count level:SHARE_LEVEL menus:share_menu];
            break;
        case ADS_SYSTEM:
            [self addCurrentView:ads_count level:ADS_LEVEL menus:ads_menu];
            break;
        case PUSH_SYSTEM:
            [self addCurrentView:push_count level:PUSH_LEVEL menus:push_menu];
            break;
        case SOCIAL_SYSTEM:
            [self addCurrentView:social_count level:SOCIAL_LEVEL menus:social_menu];
            break;
        case ANALYTICS_SYSTEM:
            [self addCurrentView:analytics_count level:ANALYTICS_LEVEL menus:analytics_menu];
            break;
        case CRASH_SYSTEM:
            [self addCurrentView:crash_count level:CRASH_LEVEL menus:crash_menu];
            break;
        case REC_SYSTEM:
            [self addCurrentView:rec_count level:REC_LEVEL menus:rec_menu];
            break;
        case ADTRACKING_SYSTEM:
            [self addCurrentView:adtracking_count level:ADTRACKING_LEVEL menus:adtracking_menu];
            break;
            
        default:
            break;
    }
}

-(id)addOneButton:(int)idx title:(NSString*)title sel:(SEL)sel rect:(CGRect)rect
{
    BButton* btn = [[BButton alloc] initWithFrame:rect type:BButtonTypeFacebook];
    [btn setTitle:title forState:(UIControlStateNormal)];
    [btn setTag:idx];
    [btn addTarget:self action:sel forControlEvents:UIControlEventTouchDown];
//    btn.backgroundColor = [UIColor grayColor];
    [[_mianCtrl view] addSubview:btn];
    return btn;
}

-(void)onAdTrackingOperation:(int)idx
{
    NSLog(@"onAdTrackingOperation:%d", idx);
    AdTracking* _adtracking = AdTracking::getInstance();
    if (_adtracking == NULL) {
        return;
    }
    
    switch (idx) {
        case ACTION_ON_REGISTER:
            _adtracking->onRegister();
            break;
        case ACTION_ON_LOGIN:
            _adtracking->onLogin();
            break;
        case ACTION_ON_PAY:
            _adtracking->onPay();
            break;
        case ACTION_ON_TRACK_EVENT:
            _adtracking->trackEvent();
            break;
        case ACTION_ON_CREATE_ROLE:
            _adtracking->onCreateRole();
            break;
        case ACTION_ON_LEVEL_UP:
            _adtracking->onLevelUp();
            break;
        case ACTION_ON_START_TO_PAY:
            _adtracking->onStartToPay();
            break;
    }
    
}

-(void)onCrashOperation:(int)idx
{
    NSLog(@"onCrashOperation:%d", idx);
    Crash* _crash = Crash::getInstance();
    if (_crash == NULL) {
        return;
    }
    
    switch (idx) {
        case ACTION_SET_USER_IDENTIFIFER:
            _crash->setUserIdentifier();
            break;
        case ACTION_REPORT_EXCEPTION:
            _crash->reportException();
            break;
        case ACTION_LEAVE_BREAD_CRUMB:
            _crash->leaveBreadcrumb();
            break;
    }
    
}


-(void)onRECOperation:(int)idx
{
    NSLog(@"onRECOperation:%d", idx);
    REC* _rec = REC::getInstance();
    if (_rec == NULL) {
        return;
    }
    
    switch (idx) {
        case ACTION_STARTRECORDING:
            _rec->setMetaData();
            _rec->startRecording();
            break;
        case ACTION_STOPRECORDING:
            NSLog(@"isRecording:%s", _rec->isRecording()?"true":"false");
            _rec->stopRecording();
            break;
        case ACTION_SHAREVIDEO:
            _rec->share();
            break;
        case ACTION_PAUSECORDING:
            _rec->pauseRecording();
            break;
        case ACTION_RESUMECORDING:
            _rec->resumeRecording();
            break;
        case ACTION_SHOWTOOLBAR:
            _rec->showToolBar();
            break;
        case ACTION_HIDETOOLBAR:
            _rec->hideToolBar();
            break;
        case ACTION_SHOWVIDEOCENTER:
            _rec->showVideoCenter();
            break;
        case ACTION_ENTERPLATFORM:
            NSLog(@"isAvailable:%s", _rec->isAvailable()?"true":"false");
            _rec->enterPlatform();
            break;
    }
    
}

-(void)onPushOperation:(int)idx
{
    NSLog(@"on push action: %d", idx);
    Push* _push = Push::getInstance();
    switch (idx) {
        case START_PUSH:{
            _push->startPush();
        }
            break;
        case CLOSE_PUSH:
            _push->closePush();
            break;
        case SET_ALIAS:
            _push->setAlias();
            break;
        case DEL_ALIAS:
            _push->delAlias();
            break;
        case SET_TAGS:{
            _push->setTags();
        }
            break;
        case DEL_TAGS:{
            _push->delTags();
        }
            break;
            
        default:
            break;
    }
}

-(void)onAnalyticsOperation:(int)idx
{
    NSLog(@"on analytics action: %d", idx);
    Analytics* _analytics = Analytics::getInstance();
    switch (idx) {
        case LOG_EVENT:
            _analytics->logEvent("1001");
            _analytics->startSession();
            _analytics->stopSession();
            _analytics->logTimedEventBegin("1003");
            _analytics->logTimedEventEnd("1004");
            _analytics->isFunctionSupported("stopSession");
            _analytics->setSessionContinueMillis(100);
            _analytics->setCaptureUncaughtException(true);
            break;
        case LOG_ERROR:
            _analytics->logError("1003", "err msg!");
            _analytics->startLevel();
            _analytics->setAccount();
            _analytics->onChargeFail();
            _analytics->onChargeOnlySuccess();
            _analytics->onChargeRequest();
            _analytics->failLevel();
            _analytics->finishLevel();
            break;
            
        default:
            break;
    }
}

-(void)onSocialOperation:(int)idx
{
    NSLog(@"on social action: %d", idx);
    Social* _social = Social::getInstance();
    switch (idx) {
        case SUBMIT_SCORE:
            _social->submitScore();
            break;
        case SHOW_LEADERBOARD:
            _social->showLeaderboard();
            break;
        case UNLOCK_ACHIEVEMENT:{
            _social->unlockAchievement();
        }
            break;
        case SHOW_ACHIEVEMENTS:
            _social->showAchievements();
            break;
            
        default:
            break;
    }
}

-(void)onBannerViews:(int)idx
{
    Ads* _ads = Ads::getInstance();
    if (_ads == nil) {
        return;
    }
    switch (idx) {
        case SHOW_BANNER_1:
            _ads->showAds(AD_TYPE_BANNER, 1);
            break;
        case HIDE_BANNER_1:
            _ads->hideAds(AD_TYPE_BANNER, 1);
            break;
        case SHOW_BANNER_2:
            _ads->showAds(AD_TYPE_BANNER, 2);
            break;
        case HIDE_BANNER_2:
            _ads->hideAds(AD_TYPE_BANNER, 2);
            break;
        case SHOW_BANNER_3:
            _ads->showAds(AD_TYPE_BANNER, 3);
            break;
        case HIDE_BANNER_3:
            _ads->hideAds(AD_TYPE_BANNER, 3);
            break;
        case SHOW_BANNER_4:
            _ads->showAds(AD_TYPE_BANNER, 4);
            break;
        case HIDE_BANNER_4:
            _ads->hideAds(AD_TYPE_BANNER, 4);
            break;
        case SHOW_BANNER_5:
            _ads->showAds(AD_TYPE_BANNER, 5);
            break;
        case HIDE_BANNER_5:
            _ads->hideAds(AD_TYPE_BANNER, 5);
            break;
    }
}

-(void)onFullscreenViews:(int)idx
{
    Ads* _ads = Ads::getInstance();
    if (_ads == nil) {
        return;
    }
    switch (idx) {
        case SHOW_FULLSCREEN_1:
            _ads->showAds(AD_TYPE_FULLSCREEN, 1);
            break;
        case HIDE_FULLSCREEN_1:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 1);
            break;
        case SHOW_FULLSCREEN_2:
            _ads->showAds(AD_TYPE_FULLSCREEN, 2);
            break;
        case HIDE_FULLSCREEN_2:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 2);
            break;
        case SHOW_FULLSCREEN_3:
            _ads->showAds(AD_TYPE_FULLSCREEN, 3);
            break;
        case HIDE_FULLSCREEN_3:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 3);
            break;
    }
}

-(void)onMoreappViews:(int)idx
{
    Ads* _ads = Ads::getInstance();
    if (_ads == nil) {
        return;
    }
    switch (idx) {
        case SHOW_FULLSCREEN_1:
            _ads->showAds(AD_TYPE_FULLSCREEN, 1);
            break;
        case HIDE_FULLSCREEN_1:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 1);
            break;
        case SHOW_FULLSCREEN_2:
            _ads->showAds(AD_TYPE_FULLSCREEN, 2);
            break;
        case HIDE_FULLSCREEN_2:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 2);
            break;
        case SHOW_FULLSCREEN_3:
            _ads->showAds(AD_TYPE_FULLSCREEN, 3);
            break;
        case HIDE_FULLSCREEN_3:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 3);
            break;
    }
}

-(void)onOfferwallViews:(int)idx
{
    Ads* _ads = Ads::getInstance();
    if (_ads == nil) {
        return;
    }
    switch (idx) {
        case SHOW_OFFERWALL_1:
            _ads->showAds(AD_TYPE_OFFERWALL, 1);
            break;
        case HIDE_OFFERWALL_1:
            _ads->hideAds(AD_TYPE_OFFERWALL, 1);
            break;
        case SHOW_OFFERWALL_2:
            _ads->showAds(AD_TYPE_OFFERWALL, 2);
            break;
        case HIDE_OFFERWALL_2:
            _ads->hideAds(AD_TYPE_OFFERWALL, 2);
            break;
        case SHOW_OFFERWALL_3:
            _ads->showAds(AD_TYPE_OFFERWALL, 3);
            break;
        case HIDE_OFFERWALL_3:
            _ads->hideAds(AD_TYPE_OFFERWALL, 3);
            break;
    }
}

-(void)onAdsOperation:(int)idx
{
    NSLog(@"on ads action:%d", idx);
    if (idx >= ADS_OFFERWALL_LEVEL) {
        [self onOfferwallViews:idx-ADS_OFFERWALL_LEVEL];
        return;
    }
    if (idx >= ADS_MOREAPP_LEVEL) {
        [self onMoreappViews:idx-ADS_MOREAPP_LEVEL];
        return;
    }
    if (idx >= ADS_FULLSCREEN_LEVEL) {
        [self onFullscreenViews:idx-ADS_FULLSCREEN_LEVEL];
        return;
    }
    if (idx >= ADS_BANNER_LEVEL) {
        [self onBannerViews:idx-ADS_BANNER_LEVEL];
        return;
    }
    
    switch (idx) {
        case ADS_BANNER:
            [self addCurrentView:banner_count level:ADS_LEVEL+ADS_BANNER_LEVEL menus:banner_menu];
//                _ads->showAds(AdsType(AD_TYPE_BANNER),1);
            break;
        case ADS_FULLSCREEN:
            [self addCurrentView:fullscreen_count level:ADS_LEVEL+ADS_FULLSCREEN_LEVEL menus:fullscreen_menu];
//                _ads->hideAds(AD_TYPE_BANNER,1);
            break;
        case ADS_MOREAPP:
            [self addCurrentView:moreapp_count level:ADS_LEVEL+ADS_MOREAPP_LEVEL menus:moreapp_menu];
//                _ads->showAds(AD_TYPE_FULLSCREEN,1);
            break;
        case ADS_OFFERWALL:
            [self addCurrentView:offerwall_count level:ADS_LEVEL+ADS_OFFERWALL_LEVEL menus:offerwall_menu];
//                _ads->hideAds(AD_TYPE_FULLSCREEN,1);
            break;
        default:
            break;
    }
}
-(void)onShareOperation:(int)idx
{
    NSLog(@"on share action:%d", idx);
    
    
    Share::getInstance()->share();
}
-(void)onIAPOperation:(int)idx
{
    NSLog(@"on iap action:%d", idx);
    switch (idx) {
        case IAP_PAY:{
            PluginChannel::getInstance()->pay();
        }
            break;
        case IAP_REQUEST:{
            NSLog(@"request iap product info.");
            
            PluginChannel::getInstance()->requestProducts();
        }
            break;
            
        default:
            break;
    }
}
-(void)onUserOperation:(int)idx
{
    NSLog(@"on user action:%d", idx);
    PluginChannel* _user = PluginChannel::getInstance();
    switch (idx) {
        case USER_LOGIN:
            _user->login();
            break;
        case USER_LOGOUT:
            _user->logout();
            break;
        case USER_ENTERPLATFORM:
            _user->enterPlatform();
            break;
        case USER_SHOWTOOLBAR:
            _user->showToolBar(kToolBarBottomLeft);
            break;
        case USER_HIDETOOLBAR:
            _user->hideToolBar();
            break;
        case USER_ACCOUNTSWITCH:
            _user->accountSwitch();
            break;
        case USER_REALNAMEREGISTER:
            _user->realNameRegister();
            break;
        case USER_ANTIADDICTIONQUERY:
            _user->antiAddictionQuery();
            break;
        case USER_SUBMITLOGINGAMEROLE:{
            _user->submitLoginGameRole();
            std::string uid = _user->getUserId();
            NSLog(@"userID is:%s", uid.c_str());
            std::string pid = _user->getPluginId();
            NSLog(@"plugin ID is:%s", pid.c_str());
            std::string cid = _user->getChannelId();
            NSLog(@"ChannelID is:%s", cid.c_str());
            std::string cparam = AgentManager::getInstance()->getCustomParam();
            NSLog(@"CustomParam is:%s", cparam.c_str());
        }
            break;
            
        default:
            break;
    }
}

-(void)onClick:(id)btn
{
    int idx = [btn tag];
    if (idx == BACK_BUTTON) {
        [self hideCurView];
        [_mianCtrl showBaseBtns];
    }
    else if (idx>=ADTRACKING_LEVEL) {
        [self onAdTrackingOperation:idx-ADTRACKING_LEVEL];
    }
    else if (idx>=REC_LEVEL) {
        [self onRECOperation:idx-REC_LEVEL];
    }
    else if (idx>=CRASH_LEVEL) {
        [self onCrashOperation:idx-CRASH_LEVEL];
    }
    else if (idx>=ANALYTICS_LEVEL) {
        [self onAnalyticsOperation:idx-ANALYTICS_LEVEL];
    }
    else if (idx>=PUSH_LEVEL) {
        [self onPushOperation:idx-PUSH_LEVEL];
    }
    else if (idx>=SOCIAL_LEVEL){
        [self onSocialOperation:idx-SOCIAL_LEVEL];
    }
    else if (idx>=ADS_LEVEL){
        [self onAdsOperation:idx-ADS_LEVEL];
    }
    else if (idx>=SHARE_LEVEL){
        [self onShareOperation:idx-SHARE_LEVEL];
    }
    else if (idx>=IAP_LEVEL){
        [self onIAPOperation:idx-IAP_LEVEL];
    }
    else if (idx>=USER_LEVEL){
        [self onUserOperation:idx-USER_LEVEL];
    }
}

-(void)hideCurView
{
    if (_views.size() < 1) {
        return;
    }
    LIST_VIEW::iterator iter;
    for (iter = _views.begin(); iter != _views.end(); iter++) {
        [*iter setHidden:true];
        [*iter removeFromSuperview];
    }
    _views.clear();
    
    [backBtn setHidden:true];
}

-(void)resetBackBtn:(int)count
{
    backBtn.frame = CGRectMake(0, ([ViewController getButtonSize].height+SPACE_H)*count + BASE_FULLSCREEN_Y, [ViewController getButtonSize].width, [ViewController getButtonSize].height);
    if ([backBtn isHidden]) {
        [backBtn setHidden:false];
    }
}

+(void)addToast:(NSString*)content
{
    [_mianCtrl showToast:content];
}

+(void)addDebugView:(NSString*)title ctx:(NSString*)content
{
    [_mianCtrl addDebugView:title ctx:content];
}

+(void)addButtons:(NSDictionary*)array
{
    [_instance hideCurView];
    
    int count = [array count];
    NSArray* _keys = [array allKeys];
    float _w = [ViewController getButtonSize].width;
    float _h = [ViewController getButtonSize].height;
    for (int i=0; i<count; i++) {
        NSLog(@"key:%@, value:%@", _keys[i], [array objectForKey:_keys[i]]);
        UIButton* btn = [_instance addOneButton:[_keys[i] intValue] title:[array objectForKey:_keys[i]] sel:@selector(onSelectPayMode:) rect:CGRectMake(0, (_h+SPACE_H)*i + BASE_FULLSCREEN_Y, _w, _h)];
        _views.push_back(btn);
    }
    [_instance resetBackBtn:count];
}
-(void)onSelectPayMode:(id)btn
{
    int tag = [btn tag];
    NSLog(@"tag:%d", tag);
    PluginChannel::getInstance()->payMode([[[NSString alloc] initWithFormat:@"%d",tag] UTF8String]);
}

-(void)addCurrentView:(int)count level:(int)level menus:(std::string*)menus
{
    float _w = [ViewController getButtonSize].width;
    float _h = [ViewController getButtonSize].height;
    for (int i=0; i<count; i++) {
        NSString* tempTitle = [NSString stringWithUTF8String:menus[i].c_str()];
        UIButton* btn = [self addOneButton:level+i title:tempTitle sel:@selector(onClick:) rect:(CGRectMake(0, (_h+SPACE_H)*i + BASE_FULLSCREEN_Y, _w, _h))];
        _views.push_back(btn);
    }
    [self resetBackBtn:count];
}

@end
