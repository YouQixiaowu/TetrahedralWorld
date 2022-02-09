#pragma once
namespace tw
{
    class Window
    {
    public:
        __declspec(dllexport) Window(const std::string& name);
        __declspec(dllexport) ~Window();
        /// <summary>
        /// ������Ϣѭ��
        /// </summary>
        __declspec(dllexport) void employ();
        /// <summary>
        /// ֪ͨ�߳�ʹ����ֹ
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
