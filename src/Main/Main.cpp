#include "pch.h"
#include "windows.h" 

int main()
{
    CHAR exeFullPath[1024]; // MAX_PATH
    GetModuleFileNameA(NULL, exeFullPath, 1024);
    std::string path = exeFullPath;
    tw::SettingsData::set("val", "123");
    tw::Window::start();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    tw::Window::stop();
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