#pragma once
#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ�ļ����ų�����ʹ�õ�����
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
        /// ������Ϣѭ��
        /// </summary>
        __declspec(dllimport) void employ();
        /// <summary>
        /// ֪ͨ�߳�ʹ����ֹ
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
