#pragma warning(disable:4996)
#include "pch.h"
#include <iostream>
#include <iomanip>
namespace tw
{
    void Log::print(const std::string& infor, Level level /*= LOG_INFO*/)
    {
        struct tm temp;
        const std::time_t t = std::time(nullptr);
        localtime_s(&temp, &t);
        std::cout << "[" << std::put_time(&temp, "%Y-%m-%d %H:%M:%S");

        switch (level)
        {
        case tw::Log::LOG_DEBUG:
            std::cout << "][DEBUG] : "; break;
        case tw::Log::LOG_INFO:
            std::cout << "][INFO] : "; break;
        case tw::Log::LOG_WARNING:
            std::cout << "][WARNING] : "; break;
        case tw::Log::LOG_ERROR:
            std::cout << "][ERROR] : "; break;
        case tw::Log::LOG_CRITICAL:
            std::cout << "][CRITICAL] : "; break;
        default:
            break;
        }
        std::cout << infor << std::endl;
    }

}