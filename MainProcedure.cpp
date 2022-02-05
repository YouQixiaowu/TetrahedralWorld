#include "pch.h"

namespace tw
{
    MainProcedure::MainProcedure(size_t index) :
        m_procedureIndex(index)
    {
        Supervisor& supervisor = Supervisor::_instance();
        std::unique_lock<ThreadMutex> lock(supervisor.m_mutexMain);
        if (m_procedureIndex >= supervisor.m_procedures.size())
            supervisor.m_procedures.resize(m_procedureIndex + 1);
        supervisor.m_procedures.at(m_procedureIndex).push_back(this);
    }

    MainProcedure::~MainProcedure()
    {
        Supervisor& supervisor = Supervisor::_instance();
        std::unique_lock<ThreadMutex> lock(supervisor.m_mutexMain);
        if (m_procedureIndex >= supervisor.m_procedures.size())
            return;
        std::list<MainProcedure*>& temp = supervisor.m_procedures.at(m_procedureIndex);
        for (std::list<MainProcedure*>::iterator iter = temp.begin(); iter != temp.end(); iter++)
        {
            if (*iter == this)
            {
                *iter = nullptr;
                temp.erase(iter);
                break;
            }
        }
    }
}