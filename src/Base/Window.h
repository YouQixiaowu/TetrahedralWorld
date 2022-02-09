#pragma once
namespace tw
{
    class Window
    {
    public:
        __declspec(dllexport) Window(const std::string& name);
        __declspec(dllexport) ~Window();
        /// <summary>
        /// 进入消息循环
        /// </summary>
        __declspec(dllexport) void employ();
        /// <summary>
        /// 通知线程使其终止
        /// </summary>
        __declspec(dllexport) void stop();
        virtual LRESULT _employ(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
    protected:
        HWND m_hwnd;
    private:
        friend class WindowManager;
        std::atomic<int> m_life;
    };

}
