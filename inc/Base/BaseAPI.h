#pragma once
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <string>
#include <windows.h>
#include <atomic>
namespace tw
{
    class Window
    {
    public:
        __declspec(dllimport) Window(const std::string& name);
        __declspec(dllimport) ~Window();
        /// <summary>
        /// 进入消息循环
        /// </summary>
        __declspec(dllimport) void employ();
        /// <summary>
        /// 通知线程使其终止
        /// </summary>
        __declspec(dllimport) void stop();
        virtual LRESULT _employ(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
    protected:
        HWND m_hwnd;
    private:
        friend class WindowManager;
        std::atomic<int> m_life;
    };
}
