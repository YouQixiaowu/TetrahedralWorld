#pragma once
namespace tw
{
    class WindowManager
    {
    public:
        static void registerInstance(Window* imp);
        static void deregisterInstance(Window* imp);
        static Window* findWindow(HWND hwnd);
    };
}