#include "pch.h"
namespace tw
{
    NamedEvent::NamedEvent(const std::string& eventName, bool needMain) :
        m_eventName(eventName),
        m_isMain(needMain)
    {
        Supervisor& supervisor = Supervisor::_instance();
        std::unique_lock<ThreadMutex> lock(supervisor.m_mutexSteward);
        supervisor.m_namedEvents[m_eventName].insert(this);
    }

    NamedEvent::~NamedEvent()
    {
        Supervisor& supervisor = Supervisor::_instance();
        std::unique_lock<ThreadMutex> lock(supervisor.m_mutexSteward);
        supervisor.m_namedEvents[m_eventName].erase(this);
    }
}