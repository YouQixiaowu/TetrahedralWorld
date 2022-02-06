#pragma once
namespace tw
{
    /// <summary>
    /// �̻߳�����
    /// </summary>
    class ThreadMutex
    {
    public:
        /// <summary>
        /// �߳���ػ�����������ͬ�߳���������
        /// </summary>
        /// <param name="threadId">�����߳�ID</param>
        ThreadMutex(std::thread::id threadId);
        /// <summary>
        /// ����
        /// </summary>
        ~ThreadMutex();
        /// <summary>
        /// ������ͬ�̼߳������ᱻ����
        /// </summary>
        void lock();
        /// <summary>
        /// ������ͬ�߳̽������ᱻ����
        /// </summary>
        void unlock();
        /// <summary>
        /// �����̼߳�������߳��Ƿ���ʹ����Դ�������������ͷ����������̡߳�
        /// </summary>
        void release();
        /// <summary>
        /// �����̲߳���ʹ����Դ
        /// </summary>
        void open();
        /// <summary>
        /// �����߳̿�ʼʹ����Դ
        /// </summary>
        void close();
    private:
        // �����߳�ID
        std::thread::id m_threadId;
        std::mutex m_mutex;
        // �����̷߳��ʼ�����������ζ��������������
        std::atomic<size_t> m_suspend;
        // ��Դ����״̬������״̬����Դ�����̲߳�ʹ����Դ
        bool m_openState;
    };
}