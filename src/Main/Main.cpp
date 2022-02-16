#include "pch.h"
#include "windows.h" 

int main()
{
    // 设置exe路径
    CHAR exeFullPath[1024];
    GetModuleFileNameA(NULL, exeFullPath, 1024);
    tw::RuntimeData::set("ExePath", std::string(exeFullPath));

    // 读取设置信息
    tw::SettingsData::synchronizeFromFile();

    // 加载扩展
    tw::ExtensionManager::loadExtensionFromSettings();




    //tw::Window::start();
    //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    //tw::Window::stop();
    //HINSTANCE hdll;
    //hdll = LoadLibraryA("Test.dll");
    //if (hdll == NULL)
    //{
    //    std::cout << "error" << std::endl;
    //}
    //tw::Supervisor::employ();
    return 0;
}

/*
windows

*/