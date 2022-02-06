#pragma once
namespace tw
{
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
        __declspec(dllexport) static void intend(const std::string& eventName);
        /// <summary>
        /// ������ѭ���������̵߳���һ�Σ�
        /// </summary>
        __declspec(dllexport) static void employ();
        ~Supervisor();
    private:
        Supervisor();
        Supervisor(const Supervisor&) = delete;
        void operator=(const Supervisor&) = delete;
        static std::unique_ptr<Supervisor> s_instance;
        static Supervisor& _instance();
        
        // ���߳���ܼ��̵߳��˳���־
        std::atomic<bool> m_life;
        // ���߳���ܼ��߳�ͬ����־
        std::atomic<bool> m_synchronize;
        //���߳���Ҫ������¼�
        NamedEvent* m_mainEvent;
        // ���߳���Դ��
        ThreadMutex m_mutexMain;
        // ���߳�����
        std::vector<std::list<MainProcedure*>> m_procedures;
        // ע��������¼�
        std::map<std::string, std::set<NamedEvent*>> m_namedEvents;
        // ��������¼�����
        std::queue<std::string> m_eventNames;
        // �ܼ��߳�
        std::thread m_thread;
        // �ܼ��߳���Դ��
        ThreadMutex m_mutexSteward;
        // ���߳�ѭ��
        void _mainLoop();
        // �ܼ��߳�ѭ��
        void _stewardLoop();
        friend class MainProcedure;
        friend class NamedEvent;
        friend class ExitEvent;
    };
}
