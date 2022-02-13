#pragma once
#include <string>
namespace tw
{
    class Log
    {
    public:
        enum Level
        {
            LOG_DEBUG,      // ������Ϣ
            LOG_INFO,       // ��ʾ��Ϣ
            LOG_WARNING,    // ����
            LOG_ERROR,      // �������
            LOG_CRITICAL,   // ��������
        };
        /// <summary>
        /// ��ӡ��־
        /// </summary>
        /// <param name="infor">��־��Ϣ</param>
        /// <param name="level">��־�ȼ�</param>
        __declspec(dllexport) static void print(const std::string& infor, Level level = LOG_INFO);
    };
}

