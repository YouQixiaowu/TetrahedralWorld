#pragma once
namespace tw
{
    /// <summary>
    /// 线程互斥量
    /// </summary>
    class ThreadMutex
    {
    public:
        /// <summary>
        /// 线程相关互斥量，避免同线程死锁问题
        /// </summary>
        /// <param name="threadId">所属线程ID</param>
        ThreadMutex(std::thread::id threadId);
        /// <summary>
        /// 析构
        /// </summary>
        ~ThreadMutex();
        /// <summary>
        /// 加锁，同线程加锁将会被屏蔽
        /// </summary>
        void lock();
        /// <summary>
        /// 解锁，同线程解锁将会被屏蔽
        /// </summary>
        void unlock();
        /// <summary>
        /// 所属线程检查其他线程是否有使用资源的请求，若有则释放锁给其他线程。
        /// </summary>
        void release();
        /// <summary>
        /// 所属线程不再使用资源
        /// </summary>
        void open();
        /// <summary>
        /// 所属线程开始使用资源
        /// </summary>
        void close();
    private:
        // 所属线程ID
        std::thread::id m_threadId;
        std::mutex m_mutex;
        // 其他线程访问计数，归零意味着其他访问请求
        std::atomic<size_t> m_suspend;
        // 资源开放状态，开发状态下资源所属线程不使用资源
        bool m_openState;
    };
}