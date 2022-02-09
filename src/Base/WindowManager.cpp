#include "pch.h"
#include "WindowManager.h"
namespace tw
{
    static std::map<HWND, Window*> s_hwnd2window;
    void WindowManager::registerInstance(Window* imp)
    {
        if (imp == nullptr)
            return;
        s_hwnd2window[imp->m_hwnd] = imp;
    }

    void WindowManager::deregisterInstance(Window* imp)
    {
        if (imp == nullptr)
            return;
        auto iter = s_hwnd2window.find(imp->m_hwnd);
        if (iter == s_hwnd2window.end())
            return;
        s_hwnd2window.erase(iter);
    }

    tw::Window* WindowManager::findWindow(HWND hwnd)
    {
        auto iter = s_hwnd2window.find(hwnd);
        if (iter == s_hwnd2window.end())
            return nullptr;
        return iter->second;
    }

}