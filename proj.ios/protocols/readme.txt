AnySDK_Framework_iOS_C++

v2.1.1 
库更新：
1、PluginHelper类中加pluginDecode、pluginEncode 接口

v2.1.0	— 
库更新：
1、集成iOS框架开发者需要在AppController或者AppDelegate中集成PluginApplicationDelegate重写以下相关函数:
//about user system
- (void)applicationDidEnterBackground:(UIApplication *)application ;
- (void)applicationWillEnterForeground:(UIApplication *)application ;

//about iap system
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation ;
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url;

//about push system
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken ;
- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error ;
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo;
- (void)application:(UIApplication *)application handleActionWithIdentifier:(NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo completionHandler:(void(^)())completionHandler ;
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler ;

2、新增崩溃分析类型SDK接口
3、新增录屏分享类型SDK接口
4、网络请求增加重试机制
5、优化框架代码，减少库大小
6、PluginHelp新增接口
a、解析xml接口getXMLInfoByFileName
b、获取日志模式
7、修复不添加SDK打包时不应调出Debug模式接口
8、插件自助开发增加插件自定义类型
9、修复支付EXT字段不支持jsonbug

AnySDK_Framework_iOS_C++
v2.0.0	— 2015.5.28
库更新：
1、PluginHelper 为插件自助开发所需类
2、日志统一输出标识，打包工具可设置输出级别
3、回调新增扩展code
4、废弃setDebugMode接口，统一由打包工具配置
5、废弃框架中JsonParser类，使用iOS原生NSJSONSerialization进行解析json
6、修复用户系统中login(std::string server_id, std::string oauthLoginServer = “”)重复调用出错bug
7、修复推送系统回调bug
8、修复统计系统中扩展函数调用参数错误
9、支持libstdc++的库
10、废弃loadALLPlugin接口，替换为loadAllPlugins
11、废弃unloadALLPlugin接口，替换为unloadAllPlugins



v1.5	— 2015.1.30
库更新：
1、新增AnySDK统计，该统计只是统计了接口调用的次数，以方便AnySDK产品的分析，默认是开启的，如果开发者介意改统计可以调用
AgentManager::getInstance()->setIsAnaylticsEnabled（false）关闭统计接口
2、新增getFrameworkVersion接口
