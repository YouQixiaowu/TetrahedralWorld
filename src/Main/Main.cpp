#include "pch.h"
#include "windows.h" 
namespace tw
{
    class WindowExample :public Window
    {
    public:
        WindowExample() :Window("111") {}
        ~WindowExample() {}
        virtual LRESULT _employ(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

    };
    LRESULT WindowExample::_employ(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(m_hwnd, &ps);
        }
        return 0;
        }
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
}

int main()
{
    tw::WindowExample we;
    we.employ();

    //HINSTANCE hdll;
    //hdll = LoadLibraryA("Test.dll");
    //if (hdll == NULL)
    //{
    //    std::cout << "error" << std::endl;
    //}
    //tw::Supervisor::employ();
    return 0;
}
