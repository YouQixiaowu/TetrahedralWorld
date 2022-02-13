#pragma once
#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ�ļ����ų�����ʹ�õ�����
#include <string>
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
            LOG_DEBUG,      // ������Ϣ
            LOG_INFO,       // ��ʾ��Ϣ
            LOG_WARNING,    // ����
            LOG_ERROR,      // �������
            LOG_CRITICAL,   // ��������
        };
        /// <summary>
        /// ��ӡ��־
        /// </summary>
        /// <param name="infor">��־��Ϣ</param>
        /// <param name="level">��־�ȼ�</param>
        __declspec(dllexport) static void print(const std::string& infor, Level level = LOG_INFO);
    };

    class Window
    {
    public:
        /// <summary>
        /// ��������
        /// </summary>
        __declspec(dllimport) static void start();
        /// <summary>
        /// ֹͣ�����߳�
        /// </summary>
        __declspec(dllimport) static void stop();
        __declspec(dllimport) ~Window();
    private:
        Window();
    };
}
