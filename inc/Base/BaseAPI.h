#pragma once
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <string>
#include <vector>
#include <windows.h>
#include <functional>
namespace tw
{
    class WhenDestructing
    {
    public:
        WhenDestructing(std::function<void()> fun) :
            m_fun(fun)
        {
        }
        ~WhenDestructing()
        {
            m_fun();
        }
    private:
        std::function<void()> m_fun;
        WhenDestructing(const WhenDestructing&) = delete;
        void operator=(const WhenDestructing&) = delete;
    };

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

    class Window
    {
    public:
        /// <summary>
        /// 启动窗口
        /// </summary>
        __declspec(dllimport) static void start();
        /// <summary>
        /// 停止窗口线程
        /// </summary>
        __declspec(dllimport) static void stop();
        __declspec(dllimport) ~Window();
    private:
        Window();
    };

    class Vec
    {
    public:
        __declspec(dllimport) Vec();
        __declspec(dllimport) Vec(double x, double y, double z);
        __declspec(dllimport) Vec(const Vec& ot);
        __declspec(dllimport) Vec& operator=(const Vec& ot);
        __declspec(dllimport) ~Vec();
    public:
        class Base
        {
        public:
            virtual ~Base() {}
        };
        Base* m_ptr;
    };

    class Transform
    {
    public:
        __declspec(dllimport) Transform();
        __declspec(dllimport) ~Transform();
        __declspec(dllimport) Transform(const Transform& ot);
        __declspec(dllimport) Transform operator=(const Transform& ot);
        __declspec(dllimport) Transform operator*(const Transform& ob) const;
        __declspec(dllimport) Vec operator*(const Vec& ob) const;
        __declspec(dllimport) std::vector<Vec> operator*(const std::vector<Vec>& ob) const;
        __declspec(dllimport) void act_on(Vec& ob);
        __declspec(dllimport) void act_on(std::vector<Vec>& ob);
    private:
        class Base
        {
        public:
            virtual ~Base() {}
        };
        Base* m_ptr;
    };
}
