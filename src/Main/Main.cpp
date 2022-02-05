#include "pch.h"
#include "windows.h"  

int main()
{
    HINSTANCE hdll;
    hdll = LoadLibraryA("Test.dll");
    if (hdll == NULL)
    {
        std::cout << "error" << std::endl;
    }
    tw::Supervisor::enterMainLoop();
    return 0;
}
