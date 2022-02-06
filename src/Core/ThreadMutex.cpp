#include "pch.h"
namespace tw
{
    ThreadMutex::ThreadMutex(std::thread::id threadId) :
        m_threadId(threadId),
        m_mutex(),
        m_suspend(0),
        m_openState(true)
    {
    }

    ThreadMutex::~ThreadMutex()
    {
    }

    void ThreadMutex::lock()
    {
        if (std::this_thread::get_id() == m_threadId)
            return;
        m_suspend++;
        m_mutex.lock();
    }

    void ThreadMutex::unlock()
    {
        if (std::this_thread::get_id() == m_threadId)
            return;
        m_mutex.unlock();
        m_suspend--;
    }

    void ThreadMutex::release()
    {
        if (m_suspend == 0)
            return;
        m_mutex.unlock();
        while (m_suspend != 0) {}
        m_mutex.lock();
    }

    void ThreadMutex::open()
    {
        if (!m_openState)
        {
            m_mutex.unlock();
            m_openState = true;
        }
    }

    void ThreadMutex::close()
    {
        if (m_openState)
        {
            m_mutex.lock();
            m_openState = false;
        }
    }
}