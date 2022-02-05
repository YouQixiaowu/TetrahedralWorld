#pragma once
#include <string>
#include <mutex>
namespace tw
{
    /// <summary>
    /// ���߳�����
    /// </summary>
    class MainProcedure
    {
    public:
        /// <summary>
        /// ����ע��
        /// </summary>
        /// <param name="procedureIndex">����λ�ú�</param>
        __declspec(dllimport) MainProcedure(size_t procedureIndex);
        /// <summary>
        /// ������ע��
        /// </summary>
        __declspec(dllimport) ~MainProcedure();
        /// <summary>
        /// ����ע����ִ�иú���
        /// </summary>
        virtual void execute() = 0;
    private:
        size_t m_procedureIndex;
    };

    /// <summary>
    /// �����¼�
    /// </summary>
    class NamedEvent
    {
    public:
        /// <summary>
        /// ����ע��
        /// </summary>
        /// <param name="eventName">�¼�����</param>
        __declspec(dllimport) NamedEvent(const std::string& eventName, bool needMain);
        /// <summary>
        /// ������ע��
        /// </summary>
        __declspec(dllimport) ~NamedEvent();
        /// <summary>
        /// �¼�������ʱ����ִ�иú�����
        /// </summary>
        virtual void execute() = 0;
    private:
        std::string m_eventName;
        bool m_isMain;
    };

    /// <summary>
    /// ����
    /// </summary>
    class Supervisor
    {
    public:
        /// <summary>
        /// ���������¼�������ύ�ɹܼ��߳��첽ִ�С�
        /// </summary>
        /// <param name="eventName">�����¼���</param>
        __declspec(dllimport) static void intend(const std::string& eventName);
        /// <summary>
        /// ������ѭ���������̵߳���һ�Σ�
        /// </summary>
        __declspec(dllimport) static void enterMainLoop();
        /// <summary>
        /// �����޸���
        /// </summary>
        class ThreadResourceLock
        {
        public:
            /// <summary>
            /// ����޸�Ȩ
            /// </summary>
            __declspec(dllexport) ThreadResourceLock();
            /// <summary>
            /// �ͷ��޸�Ȩ
            /// </summary>
            __declspec(dllexport) ~ThreadResourceLock();
        private:
            ThreadResourceLock(const ThreadResourceLock&) = delete;
            void operator=(const ThreadResourceLock&) = delete;
            std::mutex& _getMutex();
            std::unique_lock<std::mutex> m_lock;
        };
    private:
        Supervisor();
        Supervisor(const Supervisor&) = delete;
        void operator=(const Supervisor&) = delete;
    };
}
