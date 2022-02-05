#include "pch.h"
#include <iostream>

namespace tw
{
    Supervisor* Supervisor::s_instance = nullptr;
    static std::mutex s_mutex;

    Supervisor& Supervisor::_instance()
    {

        if (s_instance == nullptr)
        {
            std::unique_lock<std::mutex> lock(s_mutex);
            if (s_instance == nullptr)
                s_instance = new Supervisor;
        }
        return *s_instance;
    }

    Supervisor::Supervisor() :
        m_life(true),
        m_mutexMain(std::this_thread::get_id()),
        m_procedures(),
        m_namedEvents(),
        m_eventNames(),
        m_thread([&] {_stewardLoop(); }),
        m_mutexSteward(m_thread.get_id())
    {
    }

    void Supervisor::_mainLoop()
    {
        m_mutexMain.close();
        while (m_life)
        {
            for (std::list<MainProcedure*>& iter : m_procedures)
            {
                m_mutexMain.release();
                if (iter.empty())
                    continue;
                iter.back()->execute();
            }
        }
    }

    void Supervisor::_stewardLoop()
    {
        m_mutexSteward.close();
        while (m_life)
        {
            m_mutexSteward.release();
            if (m_eventNames.empty())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            else
            {
                std::string eventName = m_eventNames.front();
                auto temp = m_namedEvents.find(eventName);
                if (temp == m_namedEvents.end())
                    continue;
                for (auto iter : temp->second)
                {
                    if (iter == nullptr)
                        continue;
                    iter->execute();
                }
                m_eventNames.pop();
            }
        }
    }

    //void Supervisor::stopMainLoop()
    //{
    //    Supervisor& supervisor = _instance();
    //    supervisor.m_life = false;
    //    supervisor.m_thread.join();
    //}

    void Supervisor::enterMainLoop()
    {
        static bool one = false;
        if (one)
            return;
        one = true;
        Supervisor& supervisor = _instance();
        supervisor._mainLoop();
    }

    void Supervisor::intend(const std::string& eventName)
    {
        Supervisor& supervisor = _instance();
        std::unique_lock<ThreadMutex> lock(supervisor.m_mutexSteward);
        supervisor.m_eventNames.push(eventName);
    }

}
