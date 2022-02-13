#pragma once
#include <string>
namespace tw
{
    class Log
    {
    public:
        enum Level
        {
            LOG_DEBUG,      // 调试信息
            LOG_INFO,       // 提示信息
            LOG_WARNING,    // 警告
            LOG_ERROR,      // 常规错误
            LOG_CRITICAL,   // 致命错误
        };
        /// <summary>
        /// 打印日志
        /// </summary>
        /// <param name="infor">日志信息</param>
        /// <param name="level">日志等级</param>
        __declspec(dllexport) static void print(const std::string& infor, Level level = LOG_INFO);
    };
}

