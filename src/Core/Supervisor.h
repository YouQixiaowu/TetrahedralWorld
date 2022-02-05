#pragma once
namespace tw
{
    /// <summary>
    /// 主管
    /// </summary>
    class Supervisor
    {
    public:
        /// <summary>
        /// 触发命名事件，命令会交由管家线程异步执行。
        /// </summary>
        /// <param name="eventName">命名事件名</param>
        __declspec(dllexport) static void intend(const std::string& eventName);
        /// <summary>
        /// 进入主循环（由主线程调用一次）
        /// </summary>
        __declspec(dllexport) static void enterMainLoop();
    private:
        Supervisor();
        Supervisor(const Supervisor&) = delete;
        void operator=(const Supervisor&) = delete;
        static Supervisor* s_instance;
        static Supervisor& _instance();
        
        // 主线程与管家线程的退出标志
        std::atomic<bool> m_life;
        // 主线程资源锁
        ThreadMutex m_mutexMain;
        // 主线程流程
        std::vector<std::list<MainProcedure*>> m_procedures;
        // 注册的命名事件
        std::map<std::string, std::set<NamedEvent*>> m_namedEvents;
        // 待处理的事件名称
        std::queue<std::string> m_eventNames;
        // 管家线程
        std::thread m_thread;
        // 管家线程资源锁
        ThreadMutex m_mutexSteward;
        // 主线程循环
        void _mainLoop();
        // 管家线程循环
        void _stewardLoop();
        friend class MainProcedure;
        friend class NamedEvent;
    };
}
