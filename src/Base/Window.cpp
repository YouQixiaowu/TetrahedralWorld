#include "pch.h"
#include "WindowManager.h"
namespace tw
{
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        Window* window = WindowManager::findWindow(hwnd);
        if (window == nullptr)
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        return window->_employ(uMsg, wParam, lParam);
    }

    Window::Window(const std::string& name) :
        m_hwnd(NULL),
        m_life(1)
    {
        HINSTANCE hInstance = GetModuleHandle(NULL);
        // Register the window class.

        WNDCLASS wc = { };

        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = name.c_str();

        RegisterClass(&wc);

        // Create the window.

        m_hwnd = CreateWindowEx(
            0,                              // Optional window styles.
            name.c_str(),                   // Window class
            name.c_str(),                   // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            NULL,       // Parent window    
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
        );
        if (m_hwnd == NULL)
            return;
        WindowManager::registerInstance(this);
    }

    Window::~Window()
    {
        stop();
        while (m_life != -1) {}
        WindowManager::deregisterInstance(this);
    }

    void Window::employ()
    {
        if (m_hwnd == NULL)
            return;
        ShowWindow(m_hwnd, SW_RESTORE);
        MSG msg = { };
        while (GetMessage(&msg, NULL, 0, 0))
        {
            if (m_life == 0)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        m_life = -1;
    }

    void Window::stop()
    {
        m_life = 0;
    }
}