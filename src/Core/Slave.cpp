#include "pch.h"
namespace tw
{
    Slave::Slave() :
        m_life(true),
        m_thread([&] {loop(); })
    {
    }

    Slave::~Slave()
    {
    }

    void Slave::push(const std::string& taskName)
    {
        m_tasks.push(taskName);
    }

    void Slave::loop()
    {
        while (m_life)
        {
            if (m_tasks.empty())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            else
            {
                std::string eventName = m_tasks.front();


                m_tasks.pop();
            }
        }
    }
}
