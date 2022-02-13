#pragma once
#include <functional>
//
namespace tw
{
    class WhenDestructing
    {
    public:
        WhenDestructing(std::function<void()> fun) :
            m_fun(fun)
        {
        }
        ~WhenDestructing()
        {
            m_fun();
        }
    private:
        std::function<void()> m_fun;
        WhenDestructing(const WhenDestructing&) = delete;
        void operator=(const WhenDestructing&) = delete;
    };
}