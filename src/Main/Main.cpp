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
    tw::Supervisor::employ();
    return 0;
}
