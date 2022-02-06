#include "pch.h"
#include <iostream>
#include <memory>
namespace tw
{
    std::unique_ptr<Supervisor> Supervisor::s_instance = nullptr;
    static std::mutex s_mutex;

    Supervisor& Supervisor::_instance()
    {
        if (s_instance == nullptr)
        {
            std::unique_lock<std::mutex> lock(s_mutex);
            if (s_instance == nullptr)
                s_instance.reset(new Supervisor);
        }
        return *s_instance;
    }

    Supervisor::Supervisor() :
        m_life(true),
        m_synchronize(false),
        m_mainEvent(nullptr),
        m_mutexMain(std::this_thread::get_id()),
        m_procedures(),
        m_namedEvents(),
        m_eventNames(),
        m_thread([&] {_stewardLoop(); }),
        m_mutexSteward(m_thread.get_id())
    {
    }

    Supervisor::~Supervisor()
    {
        m_thread.join();
    }

    void Supervisor::_mainLoop()
    {
        m_mutexMain.close();
        WhenDestructing wd([&] { m_mutexMain.open(); });
        while (m_life)
        {
            if (m_synchronize)
            {
                if (m_mainEvent != nullptr)
                {
                    std::cout << "Main:" << std::endl;
                    m_mainEvent->execute();
                }
                m_mainEvent = nullptr;
                m_synchronize = false;
                if (!m_life)
                    break;
            }
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
        WhenDestructing wd([&] { m_mutexSteward.open(); });
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
                    if (iter->isMain())
                    {
                        m_mainEvent = iter;
                        m_synchronize = true;
                        while (m_synchronize)
                            m_mutexSteward.release();
                    }
                    else
                    {
                        iter->execute();
                    }
                    if (!m_life)
                        break;
                }
                m_eventNames.pop();
            }
        }
    }

    void Supervisor::employ()
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

    class ExitEvent :public NamedEvent
    {
    public:
        ExitEvent() :
            NamedEvent("Exit", true)
        {
        }
        void execute() override
        {
            Supervisor& supervisor = Supervisor::_instance();
            supervisor.m_life = false;
        }
    };
    static ExitEvent s_exitEvent;
}
