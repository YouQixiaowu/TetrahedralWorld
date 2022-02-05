#pragma once
#include <string>
#include <mutex>
namespace tw
{
    /// <summary>
    /// 主线程流程
    /// </summary>
    class MainProcedure
    {
    public:
        /// <summary>
        /// 构造注册
        /// </summary>
        /// <param name="procedureIndex">流程位置号</param>
        __declspec(dllimport) MainProcedure(size_t procedureIndex);
        /// <summary>
        /// 析构反注册
        /// </summary>
        __declspec(dllimport) ~MainProcedure();
        /// <summary>
        /// 流程注册后会执行该函数
        /// </summary>
        virtual void execute() = 0;
    private:
        size_t m_procedureIndex;
    };

    /// <summary>
    /// 命名事件
    /// </summary>
    class NamedEvent
    {
    public:
        /// <summary>
        /// 构造注册
        /// </summary>
        /// <param name="eventName">事件名称</param>
        __declspec(dllimport) NamedEvent(const std::string& eventName, bool needMain);
        /// <summary>
        /// 析构反注册
        /// </summary>
        __declspec(dllimport) ~NamedEvent();
        /// <summary>
        /// 事件被触发时，会执行该函数。
        /// </summary>
        virtual void execute() = 0;
    private:
        std::string m_eventName;
        bool m_isMain;
    };

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
        __declspec(dllimport) static void intend(const std::string& eventName);
        /// <summary>
        /// 进入主循环（由主线程调用一次）
        /// </summary>
        __declspec(dllimport) static void enterMainLoop();
        /// <summary>
        /// 流程修改锁
        /// </summary>
        class ThreadResourceLock
        {
        public:
            /// <summary>
            /// 获得修改权
            /// </summary>
            __declspec(dllexport) ThreadResourceLock();
            /// <summary>
            /// 释放修改权
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
