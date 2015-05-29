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
